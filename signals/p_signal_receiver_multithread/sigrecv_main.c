#include <stdio.h>
#include <unistd.h>
#include <string.h> // strsignal
#include <signal.h> // sigaction, struct sigaction
#include <pthread.h>


void signal_handler(int signum, siginfo_t *info, void *ucontext) {
    (void)ucontext;
    int sigval = info->si_value.sival_int;
    pid_t sender_pid = info->si_pid;
    printf("signal_handler: Otrzymano sygnał %d (%s) od procesu %d; sigval=%d\n", signum, strsignal(signum), sender_pid, sigval);
    printf("signal_handler: pthread_self = %d\n", (int)pthread_self() % 1000);
    sleep(5);
    printf("signal_handler: koniec\n");
}
//

void* thread_routine(void* dummy) {
    int ch = (int)(intptr_t)dummy;
    (void)ch;
    printf("thread_routine: pthread_self = %d\n", (int)pthread_self() % 1000);
    while(1) {
        usleep(500 * 1000);
        //printf("%c", ch);
    }
    return NULL;
}

int main(int argc, const char** argv) {
    (void)argc;
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Mój PID: %d\n", getpid());

    pthread_t table[10];
    for (int i = 0; i < 10; i++)
        pthread_create(table + i, NULL, thread_routine, (void*)((intptr_t)'A' + i));

    sleep(2); // poczekaj na start wątków...

    struct sigaction new, old;
    memset(&new, 0, sizeof(struct sigaction));
    sigemptyset(&new.sa_mask);
    new.sa_flags = SA_SIGINFO;
    new.sa_sigaction = signal_handler;

    if (sigaction(SIGINT, &new, &old) != 0) {
        perror("sigaction"); // wyświetl errno jako tekst
        return -1;
    }

    printf("main: pthread_self = %d\n", (int)pthread_self() % 1000);

    printf("Czekam na SIGINT...\n");
    while(1) {
        sleep(10);
        printf(".");
    }

    return 0;
}

