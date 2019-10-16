#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mt_inner = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mt_outer = PTHREAD_MUTEX_INITIALIZER;

void* pA(void*arg) {
    pthread_mutex_lock(&mt_outer);
    for (int i = 0; i < 10; i++) {
//        pthread_mutex_lock(&mt_inner);
        printf("A %d begin\n", i);
        usleep(10*1000); // 10ms
        printf("A %d end\n", i);
//        pthread_mutex_unlock(&mt_inner);
        usleep(10*1000); // 10ms
    }
    pthread_mutex_unlock(&mt_outer);
    return NULL;
}

void* pB(void*arg) {
    pthread_mutex_lock(&mt_outer);
    for (int i = 0; i < 10; i++) {
//        pthread_mutex_lock(&mt_inner);
        printf("B %d begin\n", i);
        usleep(10*1000); // 10ms
        printf("B %d end\n", i);
//        pthread_mutex_unlock(&mt_inner);
        usleep(10*1000); // 10ms
    }
    pthread_mutex_unlock(&mt_outer);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t th1, th2;
    pthread_create(&th1, NULL, pA, NULL);
    pthread_create(&th2, NULL, pB, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
	return 0;
}
