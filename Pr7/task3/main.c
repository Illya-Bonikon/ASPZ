#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <файл> <слово>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *search_word = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) 
        if (strstr(line, search_word) != NULL) 
            printf("%s", line);


    fclose(file);
    return 0;
}
