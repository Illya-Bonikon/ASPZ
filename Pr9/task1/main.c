#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define MAX_LINE 1024
#define UID_THRESHOLD 1000 // Або 500 — залежно від дистрибутива

int main() {
    FILE *fp;
    char line[MAX_LINE];
    int current_uid = getuid();
    int found = 0;

    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("Не вдалося виконати getent");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        // Формат: login:password:UID:GID:GECOS:home:shell
        char *username = strtok(line, ":");
        strtok(NULL, ":"); // skip password
        char *uid_str = strtok(NULL, ":");

        if (!username || !uid_str) continue;

        int uid = atoi(uid_str);
        if (uid >= UID_THRESHOLD && uid != current_uid) {
            printf("Знайдено звичайного користувача: %s (UID: %d)\n", username, uid);
            found = 1;
        }
    }

    pclose(fp);

    if (!found) {
        printf("Інших звичайних користувачів не знайдено.\n");
    }

    return 0;
}
