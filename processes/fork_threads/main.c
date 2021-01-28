#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h> // shm_open
#include <sys/wait.h> // waitpid
#include <fcntl.h> // O_*

#include <pthread.h>

void* thread_code(void* arg) {
    int id = (int)(intptr_t)(arg);
    printf("PID=%d, wątek%d: START\n", getpid(), id);
    sleep(2);
    printf("PID=%d, wątek%d: STOP\n", getpid(), id);
    return NULL;
}


int main(void) {

    pthread_t th1, th2;

    printf("START: PID=%d, PPID=%d\n", getpid(), getppid());

    pthread_create(&th1, NULL, thread_code, (void*)1);
    pthread_create(&th2, NULL, thread_code, (void*)2);

    pid_t child = fork();
    if (child != 0)
        waitpid(child, NULL, 0);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    sleep(5);
    printf("STOP: PID=%d, PPID=%d\n", getpid(), getppid());

    return 0;
}
