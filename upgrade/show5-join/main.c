#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
void* show(void*arg) {
	for (int i = 0; i < 10; i++) {
		printf("%d\n", i);
		usleep(1000000); // 1 sekunda
	}
    return NULL;
}
int main() {
    pthread_t th1, th2;
    pthread_create(&th1, NULL, show, NULL);
    pthread_create(&th2, NULL, show, NULL);
    printf("start!\n");
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
    printf("koniec!\n");
    return 0;
}

