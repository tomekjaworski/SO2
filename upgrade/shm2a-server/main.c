#include "../shm2a-server/common.h"

int main(int argc, char **argv)
{
	sem_t* sem = sem_open(COMMON_SEMAPHORE_NAME, O_CREAT, 0600, 0);
    err(sem == SEM_FAILED, "sem_open");
    
    int fd = shm_open(COMMON_FILE_NAME, O_CREAT | O_RDWR, 0600);
    err(fd == -1, "shm_open");
    
    ftruncate(fd, sizeof(struct data2_t));
    struct data2_t* pdata = (struct data2_t*)mmap(NULL, sizeof(struct data2_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    err(pdata == NULL, "mmap");

    sem_init(&pdata->cs, 1, 1); // shared, signaled
    pdata->server_pid = getpid();

    printf("Gotowe, czekam na klienta; pdata=%p...\n", (void*)pdata);
    
    int terminate = 0, counter = 0;
    while (!terminate) {
        sem_wait(sem);
        sem_wait(&pdata->cs);
        printf("[%03d:%03d]: %s\n", counter++, pdata->id, pdata->payload);
        terminate = strcasecmp(pdata->payload, "quit") == 0;
        sem_post(&pdata->cs);
    }
    munmap(pdata, sizeof(struct data2_t));
    close(fd);
    shm_unlink("/msg_data");
    sem_close(sem);
    return 0;
}
