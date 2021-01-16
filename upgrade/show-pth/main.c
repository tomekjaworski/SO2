#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
void* show(void*arg) {
    int* p = (int*)arg;
	for (int i = 0; i < 10; i++) {
		printf("%d %d\n", i, *p);
		usleep(1000000); // 1 sekunda
	}
    return NULL;
}
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    
    pthread_t th1, th2;
    int a = 1, b = 2;
    pthread_create(&th1, NULL, show, &a);
    pthread_create(&th2, NULL, show, &b);
    printf("start!\n");
    usleep(1000000 * 10); // 15 sekund
    printf("koniec!\n");
    return 0;
}

