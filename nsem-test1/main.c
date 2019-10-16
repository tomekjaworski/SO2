#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> // stałe O_*
#include <assert.h>
#include <sys/stat.h>  


int main(void)
{
    sem_t* psem = sem_open("MojSemafor2", O_CREAT, 0777, 3);
    if (psem == SEM_FAILED) { 
        perror("sem_unlink");
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
