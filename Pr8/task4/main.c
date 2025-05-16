#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork помилка");
        return 1;
    }

    printf("%d\n", pid);

    return 0;
}
