#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("🔹 Хто зараз виконує програму (whoami):\n");
    if (system("whoami") != 0) {
        perror("Помилка виконання whoami");
        return 1;
    }

    printf("\n🔹 Інформація про користувача та його групи (id):\n");
    if (system("id") != 0) {
        perror("Помилка виконання id");
        return 1;
    }

    return 0;
}
