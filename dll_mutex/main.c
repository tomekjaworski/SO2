#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct item_t {
    struct item_t *pnext, *pprev;
    int data;
};

struct dll_t {
    struct item_t *phead, *ptail;
    pthread_mutex_t sync;
    int count;
};

void dll_init(struct dll_t* plist) {
    plist->phead = plist->ptail = NULL;
    plist->count = 0;
    pthread_mutex_init(&plist->sync, NULL);
}

struct item_t* dll_new(int data) {
    struct item_t* p = (struct item_t*)calloc(1, sizeof(struct item_t));
    p->data = data;
    return p;
}

int dll_push_back(struct dll_t* plist, int data)
{
    struct item_t* pitem = dll_new(data);
    if (!pitem)
        return 1;
    pthread_mutex_lock(&plist->sync);
    if (plist->phead == NULL) {
        plist->phead = plist->ptail = pitem;
    } else
    {
        plist->ptail->pnext = pitem;
        usleep(0);
        pitem->pprev = plist->ptail;
        usleep(0);
        plist->ptail = pitem;
        usleep(0);
    }
    plist->count++;
    pthread_mutex_unlock(&plist->sync);
    return 0;
}

void* th(void*arg)
{
    struct dll_t* plist = (struct dll_t*)arg;
    for (int i = 0; i < 100; i++)
        dll_push_back(plist, i);
        
    return NULL;
}

int main(int argc, char **argv)
{
    struct dll_t l1;
    dll_init(&l1);
    
    pthread_t handles[100];
    for (int i = 0; i < 100; i++)
        pthread_create(&handles[i], NULL, th, &l1);
    
    for (int i = 0; i < 100; i++)
        pthread_join(handles[i], NULL);
    
    printf("l1.count=%d\n", l1.count);
    
    
    int sum = 0, counter2 = 0;
    for(struct item_t* pitem = l1.phead; pitem; pitem = pitem->pnext) {
        sum += pitem->data;
        counter2++;
    }
        
    printf("sum=%d; counter2=%d\n", sum, counter2);
	printf("Done!\n");
    pthread_mutex_destroy(&l1.sync); // zwolnienie mutexu
	return 0;
}

