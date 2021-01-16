#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
struct task_t{
    float* data;
    int first;
    int last;
};

void* calc(void* arg) {
    struct task_t* ptask = (struct task_t*)arg;
    for (int i = ptask->first; i <= ptask->last; i++)
        ptask->data[i] = sinf(ptask->data[i]);
    return NULL;
}
int main(int argc, char **argv)
{
    float* numbers = (float*)malloc(sizeof(float) * 1000000);
    for (int i = 0; i < 1000000; i++)
        numbers[i] = (float)rand() / RAND_MAX;
    pthread_t th1, th2;
    struct task_t task1 = {numbers, 0, 500000};
    struct task_t task2 = {numbers, 500001, 999999};
    pthread_create(&th1, NULL, calc, &task1);
    pthread_create(&th2, NULL, calc, &task2);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Done!\n");
    return 0;
}
