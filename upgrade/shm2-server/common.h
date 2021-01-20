#if !defined(_COMMON_H_)
#define _COMMON_H_

#include <stdio.h>
#include <semaphore.h> //sem*
#include <sys/mman.h> // mmap, munmap, shm_open, shm_unlink
#include <fcntl.h> // O_*
#include <stdlib.h> // exit
#include <unistd.h> // close, ftruncate
#include <string.h> // strcasecmp
#include <time.h> // time

#define PAYLOAD_SIZE 1024
struct data_t {
    sem_t cs; // sekcja krytyczna
    int id;
    char payload[PAYLOAD_SIZE];
};

static void err(int c, const char* msg) {
    if (!c)
        return;
    perror(msg);
    exit(1);
}

#endif // _COMMON_H_
