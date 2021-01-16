#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> // stałe O_*
#define SEM_NAME "MojSemafor2"

int main(void)
{
    sem_t* psem = sem_open(SEM_NAME, O_CREAT, 0600, 0);
    if (psem == SEM_FAILED) { 
        perror("sem_open");
        return 1;
    }
    
    while(1) {
        printf("Czekam na zasygnalizowanie " SEM_NAME "...\n");
        sem_wait(psem);
        
        printf("Dostałem sygnał!!\n");
    }
    

    sem_close(psem);


	return 0;
}
