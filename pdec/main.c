#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 1000;

void* dec(void*arg) {
	for (int i = 0; i < 10; i++) {
		int value = counter;
		usleep(1000);
		value--;
		usleep(1000);
		counter = value;
	}
	return NULL;
}


int main() {
	pthread_t th[10];
	for (int i = 0; i < 10; i++)
		pthread_create(&th[i], NULL, dec, NULL);

	for (int i = 0; i < 10; i++)
		pthread_join(th[i], NULL);

	printf("counter=%d\n", counter);
	return 0;
}

