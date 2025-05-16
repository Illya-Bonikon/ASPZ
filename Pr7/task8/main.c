#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int is_regular_file(const char *path) {
    struct stat sb;
    return stat(path, &sb) == 0 && S_ISREG(sb.st_mode);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char answer[4];

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    printf("Перевірка файлів у поточному каталозі...\n");

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (is_regular_file(entry->d_name)) {
            printf("Знайдено файл: %s\n", entry->d_name);
            printf("Видалити цей файл? (y/n): ");
            fgets(answer, sizeof(answer), stdin);

            if (answer[0] == 'y' || answer[0] == 'Y') {
                if (remove(entry->d_name) == 0) {
                    printf("Видалено: %s\n", entry->d_name);
                } else {
                    perror("Не вдалося видалити файл");
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
