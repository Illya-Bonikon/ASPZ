#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define LINES_PER_PAGE 20

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);           
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);         
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
    return ch;
}

void print_file_with_pause(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Не вдалося відкрити файл");
        return;
    }

    char line[1024];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        line_count++;

        if (line_count == LINES_PER_PAGE) {
            printf("-- Більше? (натисніть будь-яку клавішу) --");
            getch();  
            printf("\r                            \r");  /
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("=== Файл: %s ===\n", argv[i]);
        print_file_with_pause(argv[i]);
    }

    return 0;
}
