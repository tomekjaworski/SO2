#include <unistd.h> // getpid, getppid
#include <stdio.h>

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    fork();
    fork();
    fork();

    pid_t my_pid = getpid();
    pid_t parent_pid = getppid();
    printf("Mój PID: %d, PID rodzica: %d\n", my_pid, parent_pid);

    sleep(1);
    return 0;
}

