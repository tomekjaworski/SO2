#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int tab1[] = { 1,2,3,4,5,6,7,8,9,10,-1 };
int tab2[] = { 10,20,30,40,50,60,70,80,90,100,-1 };

void* calc(void*arg) {
	const int* tab = (const int*)arg;
	int* pint = (int*)malloc(sizeof(int));
	*pint = 0;
	for (int i = 0; i < 10; i++) {
		*pint += tab[i];
		usleep(100000); // 100ms
	}

	return pint;
}
int main() {
	pthread_t th1, th2;
	int *ret1, *ret2;
	pthread_create(&th1, NULL, calc, tab1);
	pthread_create(&th2, NULL, calc, tab2);

	pthread_join(th1, (void**)&ret1);
	pthread_join(th2, (void**)&ret2);

	printf("ret1=%d\n", *ret1);
	printf("ret2=%d\n", *ret2);

    free(ret1);
    free(ret2);

	return 0;
}
