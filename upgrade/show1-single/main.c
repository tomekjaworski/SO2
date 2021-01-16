#include <stdio.h>
#include <unistd.h>

void* show(void*arg) {
	for (int i = 0; i < 10; i++) {
		printf("%d\n", i);
	 usleep(1);
	}
    return NULL;
}
int main() {
    show(NULL);
    show(NULL);
    sleep(10);
    return 0;
}
