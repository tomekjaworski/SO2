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
    usleep(1000000 * 15); // 15 sekund
    printf("koniec!\n");
    return 0;
}

