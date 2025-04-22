#include <stdio.h>
#include <stdlib.h>

// Реалізуйте програму для аналізу вмісту /proc/self/maps.
int main() {
    FILE *fp = fopen("/proc/self/maps", "r");
    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char line[512];
    printf("Memory Map of Current Process (/proc/self/maps):\n\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
