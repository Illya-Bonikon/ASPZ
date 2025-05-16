#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define TEMP_FILE "tempfile_test.txt"

void try_read() {
    int fd = open(TEMP_FILE, O_RDONLY);
    if (fd == -1) {
        printf("❌ Читання: %s\n", strerror(errno));
    } else {
        printf("✅ Читання дозволено\n");
        close(fd);
    }
}

void try_write() {
    int fd = open(TEMP_FILE, O_WRONLY | O_APPEND);
    if (fd == -1) {
        printf("❌ Запис: %s\n", strerror(errno));
    } else {
        printf("✅ Запис дозволено\n");
        close(fd);
    }
}

int main() {
    printf("🔧 Створюємо тимчасовий файл від імені користувача %d...\n", getuid());

    FILE *fp = fopen(TEMP_FILE, "w");
    if (!fp) {
        perror("Помилка створення файлу");
        return 1;
    }
    fprintf(fp, "Тестовий запис\n");
    fclose(fp);

    printf("📄 Файл створено: %s\n", TEMP_FILE);
    printf("🔍 Перевіряємо доступ до файлу перед змінами:\n");
    try_read();
    try_write();

    printf("\n⚙️ Зміна власника та прав (виконується від імені root)...\n");

    if (chown(TEMP_FILE, 0, 0) != 0) {
        perror("chown не вдалося (ймовірно, ви не root)");
    } else {
        printf("✅ chown виконано успішно (root)\n");
    }

    if (chmod(TEMP_FILE, S_IRUSR) != 0) {
        perror("chmod не вдалося");
    } else {
        printf("✅ chmod встановив права тільки на читання для власника\n");
    }

    printf("\n🔍 Перевіряємо доступ після зміни:\n");
    try_read();
    try_write();

    printf("\n🧹 Видаляємо тимчасовий файл...\n");
    unlink(TEMP_FILE);

    return 0;
}
