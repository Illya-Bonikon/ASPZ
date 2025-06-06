#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define TIMER_SIGNAL (SIGRTMIN)
#define MAX_SIGNALS 1000

volatile sig_atomic_t signals_received = 0;

void handler(int sig, siginfo_t *si, void *context) {
    signals_received++;
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(TIMER_SIGNAL, &sa, NULL);

    timer_t timerid;
    struct sigevent sev;
    memset(&sev, 0, sizeof(sev));
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = TIMER_SIGNAL;

    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    struct itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 1000000; 
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 1000000;

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

    sleep(1);

    if (timer_delete(timerid) == -1) {
        perror("timer_delete");
    }

    printf("Сигнали отримано: %d\n", signals_received);
    printf("Сигнали загублено (орієнтовно): %d\n", 1000 - signals_received);

    return 0;
}
