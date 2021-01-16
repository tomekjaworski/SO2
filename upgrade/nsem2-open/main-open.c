#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#define SEM_NAME "MojSemafor2"


int main(int argc, char **argv)
{
	sem_t* psem = sem_open(SEM_NAME, 0);
    if (psem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    
    int counter = 0;
    do { 
        printf("Ile sygnałów wysłać? ");
        scanf("%d", &counter);
        for (int i = 0; i < counter; i++)
            sem_post(psem);
    } while(counter != 0);
    
	return 0;
}
