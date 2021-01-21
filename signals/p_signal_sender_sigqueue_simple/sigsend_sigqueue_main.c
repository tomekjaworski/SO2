#include <stdio.h>
#include <signal.h>
#include <errno.h> // errno,perror
#include <string.h> // strerror
#include <unistd.h> // getpid
#include <limits.h>

int main(void) {
    int pid, signum;

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Mój pid: %d\n", getpid());
    printf("Podaj PID procesu: ");
    scanf("%d", &pid);
    printf("Podaj identyfikator sygnału (SIGKILL=%d;SIGINT=%d;SIGUSR1=%d;SIGABRT=%d;SIGSEGV=%d): ", SIGKILL, SIGINT, SIGUSR1, SIGABRT, SIGSEGV);
    scanf("%d", &signum);

    int sigcount, sigvalue;
    printf("Ile razy wysłać sygnał? ");
    scanf("%d", &sigcount);
    printf("Wartość dodatkowa dla sigqueue: ");
    scanf("%d", &sigvalue);

    printf("Wysłano sygnał %d (%s) do %d.\n", signum, strsignal(signum), pid);

    // Wczytaj nazwę procesu (pseudoplik comm)
    char buffer[PATH_MAX];
    sprintf(buffer, "/proc/%d/cmdline", pid);
    FILE* f;
    if ((f = fopen(buffer, "rb")) == NULL) {
        printf("Brak procesu %d.\n", pid);
    } else {
        fgets(buffer, sizeof(buffer), f);
        fclose(f);
        printf("Nazwa procesu: '%s'\n", buffer);
    }

    for (int i = 0; i < sigcount; i++) {
        union sigval val = {.sival_int = sigvalue};

        printf("%d: ", i + 1);
        if (sigqueue(pid, signum, val) != 0) {
            fprintf(stderr, "sigqueue: %s (%d)\n", strerror(errno), errno);
        } else
            printf("Ok\n");
    }

    printf("Ok!");

    return 0;
}

