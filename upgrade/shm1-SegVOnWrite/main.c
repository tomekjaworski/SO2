#include <stdio.h> // fgets
#include <sys/mman.h> // funkcje shm_*
#include <unistd.h> // ftruncate
#include <fcntl.h> // stałe O_*

int main(int argc, const char **argv) {

    int fd = shm_open("shared_mem", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }
    printf("shm_fd=%d\n", fd);
    if (ftruncate(fd, sizeof(int)) != 0) {
        perror("ftruncate");
        return 1;
    }

    int* ptr = (int*)mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    } else
        printf("ptr=%p\n", (void*)ptr);

    printf("To się uda: %d\n", *ptr);
    *ptr = 123; // to już nie (SEGV)
    return 0;
}
