#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    // Блокуємо сигнал, щоб не оброблявся асинхронно
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("Waiting for SIGUSR1...\n");

    siginfo_t info;
    int sig = sigwaitinfo(&set, &info);

    if (sig == -1) {
        perror("sigwaitinfo");
        return 1;
    }

    printf("Got signal %d from PID %d\n", info.si_signo, info.si_pid);

    return 0;
}