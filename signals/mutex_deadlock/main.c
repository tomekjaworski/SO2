#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <signal.h> // sigaction
#include <errno.h> // erno
#include <string.h> // strsignal

pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

void signal_hander(int signum, siginfo_t *siginfo, void * context) {
    (void)context, (void)siginfo;

    printf("HANDLER: Otrzymano sygnał %d (%s) w wątku %d\n",
           signum, strsignal(signum), (int)pthread_self());

    printf("l");
    pthread_mutex_lock(&global_mutex);
    sleep(1); // symuluj zajętość sekcji krytycznej

    printf("u");
    pthread_mutex_unlock(&global_mutex);

}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Mój PID=%d; pthread_self()=%d\n", getpid(), (int)pthread_self());
    printf("Wykonaj polecenie 'kill -INT %d'\n", getpid());

    struct sigaction old, new;
    sigemptyset(&new.sa_mask);
    new.sa_flags = SA_SIGINFO;
    new.sa_sigaction = signal_hander;
    if (sigaction(SIGINT, &new, &old) != 0) {
        perror("sigaction");
        return -1;
    }

    for (int i = 0; i < 1000; i++) {
        printf("L");
        pthread_mutex_lock(&global_mutex);
        sleep(1); // symuluj zajętość sekcji krytycznej
        printf("U");
        pthread_mutex_unlock(&global_mutex);
    }

    if (sigaction(SIGINT, &old, NULL) != 0) {
        perror("sigaction");
        return -1;
    }

    pthread_mutex_destroy(&global_mutex);
    return 0;
}

