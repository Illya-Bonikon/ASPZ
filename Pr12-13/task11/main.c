#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Обробник із доступом до розширеної інформації
void handler(int sig, siginfo_t *info, void *ucontext) {
    fprintf(stderr, "Caught signal %d (%s)\n", sig, strsignal(sig));
    fprintf(stderr, "Fault address: %p\n", info->si_addr);
    fprintf(stderr, "Signal code: %d\n", info->si_code);
    // Можна додати backtrace(), дамп регістрів, зберегти в файл
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    int *p = NULL;
    *p = 42; // Сегментаційна помилка
}