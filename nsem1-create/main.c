#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> // stałe O_*

int main(void)
{
    sem_t* psem = sem_open("MojSemafor2", O_CREAT | O_EXCL, 0600, 3);
    if (psem == SEM_FAILED) { 
        perror("sem_open");
        return 1;
    }
    
    int counter;
    sem_getvalue(psem, &counter);
    printf("counter=%d\n", counter);

    sem_post(psem);
    
    sem_getvalue(psem, &counter);
    printf("counter=%d\n", counter);
    
    sem_close(psem);

	return 0;
}
