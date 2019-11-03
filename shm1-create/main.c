#include <stdio.h> // fgets
#include <stdint.h> // uint*
#include <sys/mman.h> // funkcje shm_*
#include <unistd.h> // ftruncate
#include <fcntl.h> // stałe O_*
#include <string.h> // str*
#include <assert.h> // assert

struct data_t {
    uint32_t len;
    char data[32 - 4];
} __attribute__((packed));
int main(int argc, char **argv) {
    assert(sizeof(struct data_t) == 32);
    int fd = shm_open("shared_mem", O_CREAT | O_RDWR, 0666); 
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }
    printf("shm_fd=%d\n", fd);
    int status = ftruncate(fd, 32);
    if (status == -1) {
        perror("ftruncate");
        return 1;
    }
    
    struct data_t* ptr = (struct data_t*)mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("ptr=%p\n", ptr);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    
    while (1) {
        printf("Enter a string: ");
        fgets(ptr->data, sizeof(ptr->data), stdin);
        ptr->len = strlen(ptr->data);
        if (ptr->len == 1)
            break;
    }
    
    status = munmap(ptr, 32);
    if (status == -1) {
        perror("munmap");
        return 1;
    }
    shm_unlink("shared_mem");
	return 0;
}
