#include <stdio.h>
#include <unistd.h>
#include <string.h> // strsignal
#include <signal.h> // sigaction, struct sigaction

void signal_handler(int signum, siginfo_t *info, void *ucontext) {
    int sigval = info->si_value.sival_int;
    pid_t sender_pid = info->si_pid;
    printf("SH: Otrzymano sygnał %d (%s) od procesu %d; sigval=%d\n", signum, strsignal(signum), sender_pid, sigval);
    sleep(1);
    printf("Ok\n");
}
//
int main(int argc, const char** argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Mój PID: %d\n", getpid());

    struct sigaction new, old;
    memset(&new, 0, sizeof(struct sigaction));
    sigemptyset(&new.sa_mask);
    new.sa_flags = SA_SIGINFO;
    new.sa_sigaction = signal_handler;

    if (sigaction(SIGINT, &new, &old) != 0) {
        perror("sigaction"); // wyświetl errno jako tekst
        return -1;
    }

    for (int i = 0;; i++) {
        printf(".");
        if (i && !(i % 100))
            printf("\n");
        usleep(500 * 1000);
    }
    return 0;
}

