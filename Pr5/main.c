#include <stdio.h>
#include <stdlib.h>

void free_memory(char *ptr) {
    free(ptr);
    printf("Пам'ять звільнена у free_memory\n");
}

void use_memory() {
    char *buffer = malloc(20);
    if (!buffer) {
        perror("malloc");
        return;
    }
    snprintf(buffer, 20, "Дані для використання");

    printf("Перед звільненням: %s\n", buffer);

    free_memory(buffer);  
    printf("Після звільнення: %s\n", buffer);	
}

int main() {
    use_memory();
    return 0;
}
