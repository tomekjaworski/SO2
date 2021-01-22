#include <stdio.h>
#include <semaphore.h>  // sem_*
#include <string.h>     // strerro
#include <errno.h>      // errno
#include <unistd.h>     // getpid
#include <signal.h>     // sigaction
#include <pthread.h>

int tid(void) {
    int id = (int)(intptr_t)pthread_self();
    return (id < 0 ? -id : id) % 100;
}

void show_error(int show_error_information,  const char * const message) {
    if (!show_error_information)
        return;
    int temp = errno;
    printf("   SHOW_ERROR [%s, thread_id=%d]: %s (errno=%d)\n", message, tid(), strerror(temp), temp);
}

void handler (int signum, siginfo_t *info, void *ctx) {
    (void)ctx;

    printf("   HANDLER[thread_id=%d]: Otrzymano sygnał %s (%d)\n", tid(), strsignal(signum), signum);
    sleep(5);
    printf("   HANDLER[thread_id=%d]: Koniec\n", tid());
}

void* thread_routine(void* arg) {
    sem_t s1, s2, s3;

    if (sem_init(&s1, 0, 0) != 0)
        show_error(1, "sem_init[1]");

    if (sem_init(&s2, 0, 0) != 0)
        show_error(1, "sem_init[2]");

    if (sem_init(&s3, 0, 0) != 0)
        show_error(1, "sem_init[3]");

    //
    //
    //

    printf("[thread_id=%d] Punkt A\n", tid());
    if (sem_wait(&s1) != 0)
        show_error(1, "sem_wait[1]");

    printf("[thread_id=%d] Punkt B\n", tid());
    if (sem_wait(&s2) != 0)
        show_error(1, "sem_wait[2]");

    printf("[thread_id=%d] Punkt C\n", tid());
    if (sem_wait(&s3) != 0)
        show_error(1, "sem_wait[3]");

    return NULL;
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Mój PID=%d\n", getpid());
    printf("Polecenie testowe: kill -INT %d", getpid());

    // ustaw obsługe sygnału INT
    struct sigaction new, old;
    memset(&new, 0, sizeof(struct sigaction));
    sigemptyset(&new.sa_mask);
    new.sa_flags = SA_SIGINFO;
    new.sa_sigaction = handler;
    if (sigaction(SIGINT, &new, &old) != 0)
        show_error(1, "sigaction");

    printf("Teraz można wysyłać sygnały...\n");

    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, thread_routine, (void*)1);
    pthread_create(&t2, NULL, thread_routine, (void*)2);
    pthread_create(&t3, NULL, thread_routine, (void*)3);

    // wątek główny
    printf("tid() dla wątku głównego: %d\n", tid());
    thread_routine(NULL);

    printf("Koniec\n");
    return 0;
}

