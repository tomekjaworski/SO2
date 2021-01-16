#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> // stałe O_*

#define SEM_NAME "MojSemafor2"
int main(void) {

    sem_t* psem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0600, 3);
    if (psem == SEM_FAILED) { 
        perror("sem_open");
        return 1;
    }
    
    int counter;
    sem_getvalue(psem, &counter);
    printf("counter=%d\n", counter);

    sem_post(psem); // +1
    
    sem_getvalue(psem, &counter);
    printf("counter=%d\n", counter);

    // zamknij nazwany semafor
    if (sem_close(psem) != 0) {
        perror("sem_close");
        return 1;
    }

    // usuń plik nazwanego semafora
    if (sem_unlink(SEM_NAME) != 0) {
        perror("sem_unlink");
        return 1;
    }

	return 0;
}
