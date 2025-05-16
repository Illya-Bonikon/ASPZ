#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char line[512];

    // Спроба виконати cat /etc/shadow через sudo
    fp = popen("sudo cat /etc/shadow", "r");
    if (fp == NULL) {
        perror("Не вдалося виконати команду");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    pclose(fp);
    return 0;
}
