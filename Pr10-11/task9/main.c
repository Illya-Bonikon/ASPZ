#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Дочірній процес
        printf("Child is running...\n");
        sleep(2);
        exit(42); // Повертає код завершення
    } else {
        // Батьківський процес
        int status;
        pid_t ended_pid = wait(&status); // Очікуємо завершення будь-якого дочірнього процесу

        if (ended_pid > 0) {
            if (WIFEXITED(status)) {
                printf("Child exited with code %d\n", WEXITSTATUS(status));
            } else {
                printf("Child terminated abnormally\n");
            }
        } else {
            perror("wait failed");
        }
    }

    return 0;
}
