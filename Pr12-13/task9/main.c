#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig, siginfo_t *si, void *context) {
    printf("Received SIGUSR1 with value: %d\n", si->si_value.sival_int);
}

int main() {
    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    pid_t pid = getpid();
    union sigval val;
    val.sival_int = 42;

    sigqueue(pid, SIGUSR1, val);

    sleep(1);
    return 0;
}
