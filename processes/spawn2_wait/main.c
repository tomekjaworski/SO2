#include <stdio.h>
#include <unistd.h> // pid_t
#include <spawn.h> // posix_spanw
#include <errno.h> // errno
#include <string.h> // strerro
#include <limits.h> // PATH_MAX
#include <sys/wait.h> // waitpid

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    pid_t child_pid;

    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    printf("SPAWNER: getpid()=%d; getppid()=%d\n", getpid(), getppid());
    printf("SPAWNER: getcwd()='%s'\n", buffer);

    char* path = "./../sample_process/sample_process";
    char* const argv[] = {
        path, // niepoprawny format ścieżki(!)
        "5", "64", "1", "0",
        "1", // 0-return;1=segv
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

    int wstatus = 0;
    status = waitpid(child_pid, &wstatus, 0);
    if (status != 0) {
        fprintf(stderr, "waitpid: %s (%d)", strerror(errno), errno);
    }

    printf("SPAWNER: waitpid WEXITSTATUS=%d\n", WEXITSTATUS(status));
    printf("SPAWNER: waitpid WIFEXITED=%d\n", WIFEXITED(status));
    printf("SPAWNER: waitpid WIFSIGNALED=%d\n", WIFSIGNALED(status));
    printf("SPAWNER: waitpid WCOREDUMP=%d\n", WCOREDUMP(status));
    printf("SPAWNER: status=%d; child_pid=%d\n", status, child_pid);
    printf("SPAWNER: koniec\n");
}

