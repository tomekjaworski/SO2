#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("START: Mój PID: %d, PID rodzica %d\n", getpid(), getppid());

    execl("/bin/ls", "-a", NULL);
    printf("KONIEC: Mój PID: %d, PID rodzica %d\n", getpid(), getppid());
    return 0;
}


