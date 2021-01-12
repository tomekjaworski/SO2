#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>
void* ala(void*arg) {
	printf(" Ala \n");
    return NULL;
}
void* ma(void*arg) {
	printf(" ma \n");
    return NULL;
}
void* kota(void*arg) {
	printf(" kota \n");
    return NULL;
}
volatile int x;
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    
    pthread_t th1, th2, th3;
    pthread_create(&th1, NULL, ala, NULL);
    pthread_create(&th2, NULL, ma, NULL);
    pthread_create(&th3, NULL, kota, NULL);
    for (x = -1000000; x < 500; x++) sin(x);
    printf("start!\n");
    usleep(1000000 * 10); // 10 sekund
    return 0;
}

