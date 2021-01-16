#include <stdio.h>
#include <unistd.h>
#define SIZE 0x1000
int main(void) {
  
    void *p;
    p = sbrk(0);
    printf("p=%p\n", p);
    p = sbrk(SIZE);
    p = sbrk(0);
    printf("p=%p\n", p);
    p = sbrk(SIZE);
    p = sbrk(SIZE);
  return 0;
}