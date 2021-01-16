#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void* ala(void*arg) {
	printf(" Ala ");
    return NULL;
}

void* ma(void*arg) {
	printf(" ma ");
    return NULL;
}

void* kota(void*arg) {
	printf(" kota ");
    return NULL;
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    for (int i = 0; i < 100; i++)
    {
        pthread_t th1, th2, th3;    
        pthread_create(&th1, NULL, ala, NULL);
        pthread_create(&th2, NULL, ma, NULL);
        pthread_create(&th3, NULL, kota, NULL);
        usleep(10000); // 10ms
        printf("\n");
    }
    printf("start!\n");
    usleep(1000000 * 10); // 10 sekund
    return 0;
}

