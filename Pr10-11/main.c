#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    } else if (pid == 0) {
        execl("./message", "message", NULL);
        perror("exec failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Дочірній процес завершився.\n");
    }

    return 0;
}
