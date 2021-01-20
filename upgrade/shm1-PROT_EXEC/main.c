#include <stdio.h> // fgets
#include <sys/mman.h> // funkcje shm_*
#include <string.h>

extern char solitude_start[], solitude_end[];

__attribute__((noinline, section(".solitude")))
int some_function(int a, int b) {
    return a * 1000 + b * 10;
}

int main(int argc, const char **argv) {
    size_t code_size = (char*)solitude_end - (char*)solitude_start;
    void* ptr = mmap(NULL, code_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    memcpy(ptr, solitude_start, code_size);
    int (*fptr)(int,int) = (int (*)(int,int))ptr;
    int result = fptr(3, 4);
    printf("some_function=%p\n", (void*)some_function);
    printf("fptr=%p, ptr=%p\n", fptr, ptr);
    printf("result=%d\n", result);

    if (munmap(ptr, code_size) != 0) {
        perror("munmap");
        return 1;
    }
    return 0;
}
