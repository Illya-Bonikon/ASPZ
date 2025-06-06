// kill_sender.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);

    if (kill(pid, SIGUSR1) == 0) {
        printf("Sent SIGUSR1 to process %d\n", pid);
    } else {
        perror("kill failed");
    }

    return 0;
}