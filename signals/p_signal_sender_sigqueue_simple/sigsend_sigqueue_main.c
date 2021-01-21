#include <stdio.h>
#include <signal.h>
#include <errno.h> // errno,perror
#include <string.h> // strerror
#include <unistd.h> // getpid

int main(void) {
    int pid, signum;

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Mój pid: %d\n", getpid());
    printf("Podaj PID procesu: ");
    scanf("%d", &pid);

    signum = SIGINT;
    union sigval value = {.sival_int = 42};

    if (sigqueue(pid, signum, value) != 0) {
        fprintf(stderr, "sigqueue: %s (%d)\n", strerror(errno), errno);
    }
    printf("Ok!");

    return 0;
}

