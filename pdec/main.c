#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int counter = 1000;

void* dec(void*arg) {
	for (int i = 0; i < 10; i++) {
		int value = counter;
		usleep(100); // można usunąc
		value--;
		usleep(100);
		counter = value;
	}
	return NULL;
}


int main() {
    
    for (int j = 0; j < 1000; j++ ){
        counter = 1000;
        pthread_t th[10];
        for (int i = 0; i < 10; i++)
            pthread_create(&th[i], NULL, dec, NULL);

        for (int i = 0; i < 10; i++)
            pthread_join(th[i], NULL);

        printf("counter=%d\n", counter);
    
    }
	return 0;
}

