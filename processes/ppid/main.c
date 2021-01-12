#include <unistd.h> // getpid, getppid
#include <stdio.h>

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);

    pid_t my_pid = getpid();
    pid_t parent_pid = getppid();

    printf("Mój PID: %d, PID rodzica: %d\n", my_pid, parent_pid);

    printf("Wciśnij dowolny klawisz...");
    getchar();
    return 0;
}

