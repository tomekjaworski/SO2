#include <stdio.h>
#include <unistd.h>

// ulimit -u N - ograniczenie liczby procesów dla danego użytkownika
// killall -u USER - zabicie wszystkich procesów użytkownika USER (Debian, pakiet psmisc)

int main(void) {
    while(1) {
        printf("PID=%d\n", getpid());
        int result = fork();
        printf("result=%d\n", result);
        if (result != 0)
            sleep(1);
    }
}

