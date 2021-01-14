#include <stdio.h>
#include <unistd.h> // pid_t
#include <spawn.h> // posix_spanw
#include <errno.h> // errno
#include <string.h> // strerro
#include <limits.h> // PATH_MAX
int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    pid_t child_pid;

    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    printf("SPAWNER: getpid()=%d; getppid()=%d\n", getpid(), getppid());
    printf("SPAWNER: getcwd()='%s'\n", buffer);

    char* path = "/bin/date";
    char* const argv[] = {
            path,
            "+%H:%M:%S %d/%m/%Y",
            NULL
    };

    int status = posix_spawn(&child_pid, path,
                             NULL,
                             NULL,
                             argv,
                             environ);

    if (status != 0) {
        fprintf(stderr, "posix_spawn: %s (%d)", strerror(errno), errno);
    }

    printf("SPAWNER: status=%d; child_pid=%d\n", status, child_pid);
    printf("SPAWNER: koniec\n");
}


