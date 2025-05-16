#include <stdio.h>
#include <stdlib.h>

void free_memory(char *ptr) {
    free(ptr);
}

void use_memory() {
    char *buffer = malloc(20);
    snprintf(buffer, 20, "Дані для використання");
    free_memory(buffer);
    printf("%s\n", buffer);  // Використання після free — помилка
}

int main() {
    use_memory();
    return 0;
}
