#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("START: Mój PID: %d, PID rodzica %d:\n", getpid(), getppid());

    pid_t fork_pid = fork();

    if (fork_pid == 0) {
        printf("POTOMEK: Mój PID: %d, PID rodzica %d.\n", getpid(), getppid());
    } else {
        printf("RODZIC: Jestem rodzicem; fork_pid=%d.\n", fork_pid);
    }

    // Włącz sleep aby wydłuzyć czas działania rodzica.
    // Jeżeli rodzic zakończy się przed uruchomieniem getppid() u potomka, to getppid() zwróci 1 (/sbin/init).
    sleep(1);
    printf("Koniec procesu (getpid=%d)\n", getpid());
    return 0;
}
