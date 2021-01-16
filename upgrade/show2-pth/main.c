#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
void* show(void*arg) {
    int* p = (int*)arg;
    pthread_t self = pthread_self();

    // NON PORTABLE:
    // Założenie: pthread_t jest realizowany jako liczba całkowita
    // Takie założenie nie musi być prawdziwe.
    unsigned long int id = (unsigned long int)self;
    // --------

	for (int i = 0; i < 10; i++) {
		printf("p=%d id=%lu i=%d\n", *p, id, i);
		usleep(1000000); // 1 sekunda
	}
    return NULL;
}
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    pthread_t th1, th2;
    int a = 1, b = 2;
    printf("Przed pthread_create\n");
    pthread_create(&th1, NULL, show, &a);
    pthread_create(&th2, NULL, show, &b);
    printf("Start!\n");

    sleep(15); // 15 sekund
    printf("Koniec!\n");

    return 0;
}

