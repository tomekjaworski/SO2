#include <stdio.h>
#include <unistd.h>

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    alarm(5);

    for(int counter = 0;; counter++) {
        printf("Counter=%d\n", counter);
        usleep(1000 * 500); // 500ms
    }

    return 0;
}

