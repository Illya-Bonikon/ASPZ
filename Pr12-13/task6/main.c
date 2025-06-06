#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// НЕбезпечно: printf(), malloc(), sleep() тощо
// БЕЗПЕЧНО: write(), _exit()

void handle_sigint(int sig) {
    const char msg[] = "Received SIGINT\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1); // reentrant-safe
}

int main() {
    signal(SIGINT, handle_sigint);

    // Основний цикл: нескінченне очікування
    while (1) {
        pause(); // чекає на сигнал
    }

    return 0;
}
