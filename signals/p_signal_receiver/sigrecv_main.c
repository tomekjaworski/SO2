#include <stdio.h>
#include <unistd.h>
#include <string.h> // strsignal
#include <signal.h> // sigaction, struct sigaction

void signal_handler_1(int signum) {
    printf("signal_handler_1: Otrzymano sygnał %d (%s)\n", signum, strsignal(signum));
}

void signal_handler_3(int signum, siginfo_t *info, void *ucontext) {
    (void)ucontext,(void)info;
    printf("signal_handler_3: Otrzymano sygnał %d (%s)\n", signum, strsignal(signum));
}

void signal_handler_3a(int signum, siginfo_t *info, void *ucontext) {
    (void)ucontext;
    int sigval = info->si_value.sival_int;
    printf("signal_handler_3: Otrzymano sygnał %d (%s); sigval=%d\n", signum, strsignal(signum), sigval);
    sleep(1);
    printf("Ok\n");
}
//
int main(int argc, const char** argv) {
    (void)argc;
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("argv[0]=%s\n", argv[0]);
    printf("Mój PID: %d\n", getpid());

    struct sigaction new, old;
#if 0
    new.sa_handler = signal_handler_1;
    if (sigaction(SIGINT, &new, &old) != 0) {
        perror("sigaction"); // wyświetl errno jako tekst
        return -1;
    }
#endif
#if 0
    new.sa_handler = signal_handler_1;
    if (sigaction(SIGINT, &new, &old) != 0 || sigaction(SIGALRM, &new, &old) != 0) {
        perror("sigaction"); // wyświetl errno jako tekst
        return -1;
    }
#endif
#if 1
    memset(&new, 0, sizeof(struct sigaction));
    sigemptyset(&new.sa_mask);
    new.sa_flags = SA_SIGINFO;
    new.sa_sigaction = signal_handler_3a;

    if (sigaction(SIGINT, &new, &old) != 0) {
        perror("sigaction"); // wyświetl errno jako tekst
        return -1;
    }
#if 0
    if (sigaction(SIGSEGV, &new, &old) != 0) {
        perror("sigaction"); // wyświetl errno jako tekst
        return -1;
    }
#endif
#endif


    for (int i = 0;; i++) {
        printf(".");
        if (i && !(i % 100)) {
            printf("\n");
            //*(volatile char*)(NULL) = 10;
        }
        usleep(500 * 1000);
    }

    return 0;
}

