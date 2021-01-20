#include <stdio.h>
#include <unistd.h>

int main(void) {
    while(1) {
        printf("PID=%d\n", getpid());
        int result = fork();
        printf("result=%d\n", result);
        if (result != 0)
            sleep(1);
    }
}

