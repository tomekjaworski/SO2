#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

sem_t semafor;

struct task_t {
    int id;
    int counter;
} infos[] = {{1},{2},{3},{4}};
int terminate;

void* routine(void*arg) {
    struct task_t* pinfo = (struct task_t*)arg;
    
    while(1) {
        sem_wait(&semafor);
        if (terminate)
            break;
        pinfo->counter++;
        printf("ID=%d; counter=%d START\n", pinfo->id, pinfo->counter);
        usleep(5 * 1000000); // jakieś zadanie
        printf("ID=%d; counter=%d STOP\n", pinfo->id, pinfo->counter);
    }
    printf("ID=%d; counter=%d (KONIEC)\n", pinfo->id, pinfo->counter);
    return NULL;
}

int main(int argc, char **argv)
{
    int hsem = sem_init(&semafor, 0 /*false*/, 0);
    assert(hsem == 0);

    terminate = 0;
    pthread_t th[4];
    for (int i = 0; i < 4; i++)
        pthread_create(th + i, NULL, routine, infos + i);
    for (int value = -1; value != 0; ) {
        printf("Wpisz liczbę do zasygnalizowania semafora: \n");
        fflush(stdout);
        scanf("%d", &value);
        if (value == 0)
            break;
        for (int i = 0; i < value; i++)
            sem_post(&semafor);
    }

    terminate = 1;
    for (int i = 0; i < 4; i++)
        sem_post(&semafor);
            
    for (int i = 0; i < 4; i++)
        pthread_join(th[i], NULL);

    sem_destroy(&semafor);
	return 0;
}
