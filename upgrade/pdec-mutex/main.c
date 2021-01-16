#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* dec(void*arg) {
	for (int i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex);
		int value = counter;
		usleep(1000);
		value--;
		usleep(1000);
		counter = value;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
	pthread_t th[10];
	for (int i = 0; i < 10; i++)
		pthread_create(&th[i], NULL, dec, NULL);
	printf("counter=%d\n", counter);
	for (int i = 0; i < 10; i++)
		pthread_join(th[i], NULL);
	printf("counter=%d\n", counter);
    usleep(1000*1000);
	return 0;
}

