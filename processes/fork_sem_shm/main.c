#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h> // shm_open
#include <sys/wait.h>

struct memory_board_t {

    float values[32];
    int count;

    float sum;
    float mean;

    sem_t job_request;
    sem_t job_reply;
    int terminate;
};
void run_calc_process(struct memory_board_t*);

#include <fcntl.h> // O_*

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("START: Mój PID: %d, PID rodzica %d:\n", getpid(), getppid());

    // przygotuj pamięć współdzieloną

    int fd = shm_open("__common_data", O_CREAT | O_RDWR | O_TRUNC, 0666);
    if (fd == -1) {
        perror("shm_open");
        return -1;
    }

    if (ftruncate(fd, sizeof(struct memory_board_t)) == -1) {
        perror("ftruncate");
        return -1;
    }

    struct memory_board_t *pmem = mmap(NULL, sizeof(struct memory_board_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (pmem == NULL) {
        perror("mmap");
        return -1;
    }

    if (sem_init(&pmem->job_reply, 1, 0) == -1) {
        perror("sem_init");
        return -1;
    }
    if (sem_init(&pmem->job_request, 1, 0) == -1) {
        perror("sem_init");
        return -1;
    }

    pid_t fork_pid = fork();

    if (fork_pid == 0) {
        run_calc_process(pmem);
        return 0;
    }

    sleep(5);
    pmem->terminate= 1;
    sem_post(&pmem->job_request);

    waitpid(fork_pid, NULL, 0);

    printf("Koniec procesu (getpid=%d)\n", getpid());
    return 0;
}

void run_calc_process(struct memory_board_t* pmem) {
    printf("run_calc_process: START, getpid()=%d, getppid()=%d\n", getpid(), getppid());

    while(1) {
        sem_wait(&pmem->job_request);
        if (pmem->terminate)
            break;

        float sum = 0;
        for (int i = 0; i < pmem->count; i++)
            sum += pmem->values[i];

        pmem->sum = sum;
        pmem->mean = sum / (float) pmem->count;

        sem_post(&pmem->job_reply);
    }
    printf("run_calc_process: KONIEC\n");
}
