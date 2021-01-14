#include <stdio.h>
#include <semaphore.h> // sem_*
#include <errno.h> // errno
#include <string.h> // strerror
#include <time.h> // clock_settime

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    sem_t s1;
    if (sem_init(&s1, 0, 123) != 0)
        perror("sem_init");

    int value;
    if (sem_getvalue(&s1, &value) != 0)
        perror("sem_getvalue");

    printf("sem_getvalue = %d\n", value);

    //
    //
    //

    sem_t s2;
    if (sem_init(&s2, 0, 2) != 0)
        perror("sem_init");

    sem_getvalue(&s2, &value);
    printf("[1] sem_getvalue=%d\n", value);

    sem_post(&s2); // +1
    sem_getvalue(&s2, &value);
    printf("[2] sem_getvalue=%d\n", value);

    sem_wait(&s2); // -1
    sem_getvalue(&s2, &value);
    printf("[3] sem_getvalue=%d\n", value);

    sem_destroy(&s2);

    //
    //
    //

    sem_t s3;
    if (sem_init(&s3, 0, 3) != 0)
        perror("sem_init");

    sem_getvalue(&s3, &value);
    printf("[trywait] sem_getvalue=%d (start, EAGAIN=%d)\n", value, EAGAIN);

    for (int i = 0; ; i++ ) {
        int status = sem_trywait(&s3);
        if (status != 0) {
            int old_errno = errno;
            printf("sem_trywait: errno=%d, strerro=%s\n", old_errno, strerror(old_errno));
            break;
        }
        sem_getvalue(&s3, &value);
        printf("[trywait] sem_getvalue=%d\n", value);
    }

    //
    //
    //

    sem_t s4;
    sem_init(&s4, 0, 1);

    sem_wait(&s4);

    struct timespec interval;
    clock_gettime(CLOCK_REALTIME, &interval);
    interval.tv_sec += 10;

    if (sem_timedwait(&s4, &interval) != 0) {
        int old_errno = errno;
        printf("sem_timedwait: errno=%d, strerro=%s, ETIMEDOUT=%d\n", old_errno, strerror(old_errno), ETIMEDOUT);
    }

    //
    //
    //



    return 0;


}

