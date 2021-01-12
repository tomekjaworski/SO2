#include <stdio.h> // setvbuf
#include <unistd.h> // getpid, getppid
#include <stdlib.h> // atoi
#include "../ansi_colors.h"

enum terminate_method_t {
    terminate_normal = 0,
    terminate_segv = 1,
};

int main(int argc, const char **argv, const char **envp) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    if (argc < 6) {
        printf("Wywołanie:\n\tsample_process [czas] [kod błędu] [pokaż argumenty] [pokaż środowisko] [sposób wyjścia]\n");
        return 0;
    }

    int time = atoi(argv[1]); // czas, w sekundach, działania procesu
    int error = atoi(argv[2]); // kod błędu do zwrócenia po pomyślnym zakończeniu działania
    int show_argv = atoi(argv[3]); // czy wyświetlać listę argumentów procesu?
    int show_envp = atoi(argv[4]); // czy wyświetlać listę zmiennych środowiskowych?
    enum terminate_method_t term_method = (enum terminate_method_t) atoi(
            argv[5]); // jak zakończyć proces? 0=normalnie, 1=SEGV

    printf(ANSI_FG_RED "SAMPLE: getpid()=%d, getppid()=%d\n" ANSI_RESET, getpid(), getppid());

    printf(ANSI_FG_GREEN "SAMPLE: argc=%d\n" ANSI_RESET, argc);
    for (int i = 0; i < argc && show_argv; i++) {
        printf(ANSI_FG_GREEN "SAMPLE: argv[%d]='%s'\n" ANSI_RESET, i, argv[i]);
    }

    for (int i = 0; envp[i] != NULL && show_envp; i++) {
        printf(ANSI_FG_GREEN "SAMPLE: envp[%d]='%s'\n ANSI_RESET", i, envp[i]);
    }

    for (int i = 0; i < time; i++) {
        printf(ANSI_FG_GREEN "." ANSI_RESET);
        sleep(1);
    }

    printf(ANSI_FG_RED "SAMPLE: getpid()=%d - KONIEC\n" ANSI_RESET, getpid());
    if (term_method == terminate_segv) {
        volatile int dummy = *(volatile int*)(NULL);
        (void)dummy;
    }
    return error;
}

