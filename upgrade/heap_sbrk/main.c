#include <stdio.h>
#include <unistd.h>

#define PAGE_SIZE 0x1000

int main(void) {
    void *result;

    // Wyłaczenie buforowania stdout jest konieczne.
    // Przy domyślnie włączonym buforowaniu printf() uruchomi malloc() który uruchomi sbrk(),
    // co zakłóci wartości zwracane w poniższym kodzie:
    setvbuf(stdout, NULL, _IONBF, 0);

    result = sbrk(0);
    printf("[ 1] p=%p\n", result);
    printf("[ 1] p=%p\n", sbrk(0));

    result = sbrk(0);
    printf("[ 2] p=%p\n", result);
    printf("[ 2] p=%p\n", sbrk(0));

    result = sbrk(PAGE_SIZE);
    printf("[ 3] p=%p\n", result);
    printf("[ 3] p=%p\n", sbrk(0));

    result = sbrk(0);
    printf("[ 4] p=%p\n", result);
    printf("[ 4] p=%p\n", sbrk(0));

    result = sbrk(PAGE_SIZE);
    printf("[ 5] p=%p\n", result);
    printf("[ 5] p=%p\n", sbrk(0));

    result = sbrk(PAGE_SIZE);
    printf("[ 6] p=%p\n", result);
    printf("[ 6] p=%p\n", sbrk(0));

    result = sbrk(0x100);
    printf("[ 7] p=%p\n", result);
    printf("[ 7] p=%p\n", sbrk(0));

    result = sbrk(0x200);
    printf("[ 8] p=%p\n", result);
    printf("[ 8] p=%p\n", sbrk(0));

    result = sbrk(0x300);
    printf("[ 9] p=%p\n", result);
    printf("[ 9] p=%p\n", sbrk(0));

    result = sbrk(1);
    printf("[10] p=%p\n", result);
    printf("[10] p=%p\n", sbrk(0));

    result = sbrk(2);
    printf("[11] p=%p\n", result);
    printf("[11] p=%p\n", sbrk(0));

    return 0;
}
