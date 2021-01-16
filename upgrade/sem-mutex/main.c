#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

int counter = 1000;
sem_t semafor;
pthread_mutex_t mutex;

void* dec(void*arg) {
	for (int i = 0; i < 10; i++) {
		//pthread_mutex_lock(&mutex);
        //sem_wait(&semafor);
		int value = counter;
		usleep(1000);
		value--;
		usleep(1000);
		counter = value;
        //sem_post(&semafor);
		//pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
    sem_init(&semafor, 0 /*false*/, 1);
    //pthread_mutex_init(&mutex, NULL);
	pthread_t th[10];
	for (int i = 0; i < 10; i++)
		pthread_create(&th[i], NULL, dec, NULL);
	printf("counter=%d\n", counter);
	for (int i = 0; i < 10; i++)
		pthread_join(th[i], NULL);
	printf("counter=%d\n", counter);
    //pthread_mutex_destroy(&mutex);
    sem_close(&semafor);
	return 0;
}


