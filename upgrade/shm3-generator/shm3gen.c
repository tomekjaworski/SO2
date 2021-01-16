#include "../shm3-sumator/common.h"

int main(int argc, char **argv)
{
   
    int fd = shm_open("/sum_data", O_RDWR, 0600);
    err(fd == -1, "shm_open");
    
    struct ipc_data_t* pdata = (struct ipc_data_t*)mmap(NULL, sizeof(struct ipc_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    err(pdata == NULL, "mmap");
    
    srand(time(NULL));
    setvbuf (stdout, NULL, _IONBF, BUFSIZ);
    while (1) {
        
        printf("Czekam... ");
        sem_wait(&pdata->request_new_data);
        printf("Ok ");
        
        usleep(1000);
        
        int val = rand() % 100;
        printf("Dodawanie %d... ", val);
        
        usleep(1000000 * 2);

        sem_wait(&pdata->array_cs);
        if (pdata->count >= CAPACITY) {
            printf("Pojemność przekroczona\n");
            sem_post(&pdata->array_cs);
            continue;
        }
        pdata->data[pdata->count++] = val;
        sem_post(&pdata->array_cs);

        printf("Ok!\n");
        
        sem_post(&pdata->got_new_data);
    }
    
}
