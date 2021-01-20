#include "common.h"
int main(int argc, char **argv) {
    int fd = shm_open("/sum_data", O_CREAT | O_RDWR, 0600);
    err(fd == -1, "shm_open");
    
    ftruncate(fd, sizeof(struct ipc_data_t));
    struct ipc_data_t* pdata = (struct ipc_data_t*)mmap(NULL, sizeof(struct ipc_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    err(pdata == NULL, "mmap");
    
    sem_init(&pdata->array_cs, 1, 1); 
    sem_init(&pdata->got_new_data, 1, 0);
    sem_init(&pdata->request_new_data, 1, 0);

    while(1)
    {
        for (int i = 0; i < CAPACITY; i++)
            sem_post(&pdata->request_new_data);
        
        printf("Czekam na dane\n");
        // Czekaj na dane
        for (int i = 0; i < CAPACITY; i++)
            sem_wait(&pdata->got_new_data);
        
        sem_wait(&pdata->array_cs);
        printf("Liczby w tablicy: ");
        int sum = 0;
        for (int i = 0; i < pdata->count; i++) {
            printf("%d ", pdata->data[i]);
            sum += pdata->data[i];
        }
        printf("\nSuma=%d\n", sum);
        pdata->count = 0;
        sem_post(&pdata->array_cs);
    }
	return 0;
}
