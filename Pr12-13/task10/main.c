// crash_graceful.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Обробник крашу, що виконує безпечну очистку
void handler(int sig) {
    write(STDERR_FILENO, "Graceful shutdown due to signal\n", 33);
    // Тут можуть бути дії: закриття сокетів, файлів тощо
    _exit(1); // Використовуємо _exit, бо він безпечний
}

int main() {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigaction(SIGSEGV, &sa, NULL); // або SIGFPE, SIGBUS, SIGILL…

    int *p = NULL;
    *p = 42; // Спроба запису в NULL — викликає SIGSEGV
}
