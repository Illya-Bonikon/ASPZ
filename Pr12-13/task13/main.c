#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void dummy_handler(int sig) {
    // просто для демонстрації переривання sleep
    write(STDOUT_FILENO, "Signal caught\n", 14);
}

int main() {
    struct sigaction sa = {0};
    sa.sa_handler = dummy_handler;
    sigaction(SIGUSR1, &sa, NULL);

    struct timespec req = {5, 0}; // спати 5 секунд
    struct timespec rem;

    while (nanosleep(&req, &rem) == -1) {
        if (errno == EINTR) {
            req = rem; // оновити залишок
            printf("Sleep interrupted, resuming...\n");
        } else {
            perror("nanosleep failed");
            break;
        }
    }

    printf("Sleep complete\n");
}