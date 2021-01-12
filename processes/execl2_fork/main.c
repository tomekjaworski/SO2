#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> // waitpid

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("START: Mój PID: %d, PID rodzica %d\n", getpid(), getppid());

    pid_t cpid = fork();
    if (cpid == 0)
        execl("/bin/ls", "-a", NULL);
    printf("KONIEC: Mój PID: %d, PID rodzica %d\n", getpid(), getppid());
    return 0;
}

