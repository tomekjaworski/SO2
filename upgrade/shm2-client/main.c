#include "common.h"

int main(int argc, char **argv)
{
    sem_t* sem = sem_open("/msg_signal", 0);
    err(sem == SEM_FAILED, "sem_open");
    
    int fd = shm_open("/msg_data", O_RDWR, 0600);
    err(fd == -1, "shm_open");
    
    struct data_t* pdata = (struct data_t*)mmap(NULL, sizeof(struct data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    err(pdata == NULL, "mmap");
    
    srand(time(NULL));
    int my_id = rand() % 1000;
    printf("Identyfikator sesji: %d; pdata=%p......\n", my_id, pdata);
    while(1) {
        char msg[PAYLOAD_SIZE];
        printf("Podaj tekst: ");
        char* p = fgets(msg, PAYLOAD_SIZE, stdin);
        if (!p) break;
        if (*msg)
            msg[strlen(msg) - 1] = '\x0';
        
        sem_wait(&pdata->cs);
        strcpy(pdata->payload, msg);
        pdata->id = my_id;
        sem_post(&pdata->cs);
        
        sem_post(sem);
    }
    sem_close(sem);
    munmap(pdata, sizeof(struct data_t));
    close(fd);
	return 0;
}
