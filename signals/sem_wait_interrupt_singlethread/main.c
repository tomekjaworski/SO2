#include <stdio.h>
#include <semaphore.h>  // sem_*
#include <string.h>     // strerro
#include <errno.h>      // errno
#include <unistd.h>     // getpid
#include <signal.h>     // sigaction

void show_error(int show_error_information, const char * const message) {
    if (!show_error_information)
        return;
    int temp = errno;
    printf("SHOW_ERROR [%s]: %s (errno=%d)\n", message, strerror(temp), temp);
}

void handler (int signum, siginfo_t *info, void *ctx) {
    (void)ctx;

    printf("HANDLER: Otrzymano sygnał %s (%d)\n", strsignal(signum), signum);
}

int main(void) {
    sem_t s1, s2, s3;
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Mój PID=%d\n", getpid());

    // ustaw obsługe sygnału INT
    struct sigaction new, old;
    memset(&new, 0, sizeof(struct sigaction));
    sigemptyset(&new.sa_mask);
    new.sa_flags = SA_SIGINFO;
    new.sa_sigaction = handler;
    if (sigaction(SIGINT, &new, &old) != 0)
        show_error(1, "sigaction");


    if (sem_init(&s1, 0, 0) != 0)
        show_error(1, "sem_init[1]");

    if (sem_init(&s2, 0, 0) != 0)
        show_error(1, "sem_init[2]");

    if (sem_init(&s3, 0, 0) != 0)
        show_error(1, "sem_init[3]");

    printf("Teraz można wysyłać sygnały...\n");

    printf("Punkt A\n");
    if (sem_wait(&s1) != 0)
        show_error(1, "sem_wait[1]");

    printf("Punkt B\n");
    if (sem_wait(&s2) != 0)
        show_error(1, "sem_wait[2]");

    printf("Punkt C\n");
    if (sem_wait(&s3) != 0)
        show_error(1, "sem_wait[3]");

    printf("Koniec\n");
    return 0;
}

