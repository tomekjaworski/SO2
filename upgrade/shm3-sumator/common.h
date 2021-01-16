#if !defined(_COMMON_H_)
#define _COMMON_H_

#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

#define CAPACITY    10
struct ipc_data_t {
    int count;
    int data[CAPACITY];
    
    sem_t array_cs;
    sem_t got_new_data;
    sem_t request_new_data;
};


static void err(int c, const char* msg) {
    if (!c)
        return;
    perror(msg);
    exit(1);
}

#endif // _COMMON_H_
