#include <stdio.h>
#include <unistd.h>

void* show(void*arg) {
	for (int i = 0; i < 10; i++) {
		printf("%d\n", i);
	 usleep(1000000); // 1 sekunda
	}
    return NULL;
}
int main() {
    show(NULL);
    show(NULL);
    usleep(1000000 * 10); // 10 sekund
    return 0;
}
