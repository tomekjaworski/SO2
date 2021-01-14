#include <stdio.h> // setvbuf
#include <unistd.h>

int main(int argc, const char **argv, const char **envp) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

#if 1
    execl("/bin/sh", "/bin/sh", "-c", "ls", NULL);
#else
    execl("/bin/ls", "/bin/ls", "/", NULL);
#endif
}

