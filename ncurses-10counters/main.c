#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>

pthread_mutex_t nc = PTHREAD_MUTEX_INITIALIZER;
pthread_t th[10];
int rows[10];

void* thread_main(void*arg) {

    uint64_t id = (uint64_t)arg;
    char str[32];
    
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&nc);
        move(rows[id], 10);
        usleep(1000);
        
        sprintf(str, "%d-%d", id, i);
        addstr(str);
        refresh();
        pthread_mutex_unlock(&nc);
        
        usleep(1);
    }        
}

int main() {
    initscr();
    cbreak();
    noecho();
    for (uint64_t i = 0; i < 10; i++) {
        rows[i] = i;
        pthread_create(&th[i], NULL, thread_main, (void*)i);
    }
    getch();
}

