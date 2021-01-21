#include <stdio.h>
#include <signal.h>
#include <errno.h> // errno,perror
#include <string.h> // strerror
#include <unistd.h> // getpid
#include <limits.h>

int main(void) {
    int pid, signum;
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Mój PID: %d\n", getpid());
    printf("Podaj PID procesu: ");
    scanf("%d", &pid);
    printf("Podaj identyfikator sygnału (SIGKILL=%d;SIGINT=%d;SIGUSR1=%d;SIGABRT=%d;SIGSEGV=%d): ", SIGKILL, SIGINT, SIGUSR1, SIGABRT, SIGSEGV);
    scanf("%d", &signum);

    printf("Wysyłanie sygnału %d (%s) do %d.\n", signum, strsignal(signum), pid);

    // Wczytaj nazwę procesu (pseudoplik commandline)
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

    if (kill(pid, signum) != 0) {
        fprintf(stderr, "kill: %s (%d)", strerror(errno), errno);
    }
    printf("Ok!");
    return 0;
}

