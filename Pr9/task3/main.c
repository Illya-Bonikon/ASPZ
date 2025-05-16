#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	const char *userfile = "userfile.txt";
	const char *copiedfile = "/home/your_username/copiedfile.txt"; // 🔁 Заміни на свій реальний шлях

	printf("1. Створення файлу від звичайного користувача...\n");

	int fd = open(userfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}

	write(fd, "Це файл звичайного користувача.\n", 34);
	close(fd);

	printf("2. Копіювання файлу у домашній каталог як root...\n");
	char command[512];

	snprintf(command, sizeof(command), "sudo cp %s %s", userfile, copiedfile);
	if (system(command) != 0)
	{
		perror("cp failed");
		return 1;
	}

	snprintf(command, sizeof(command), "sudo chown root:root %s", copiedfile);
	if (system(command) != 0)
	{
		perror("chown failed");
		return 1;
	}

	snprintf(command, sizeof(command), "sudo chmod 600 %s", copiedfile);
	if (system(command) != 0)
	{
		perror("chmod failed");
		return 1;
	}

	printf("3. Спроба змінити файл як звичайний користувач...\n");
	snprintf(command, sizeof(command), "echo \"Додаємо текст\" >> %s", copiedfile);
	if (system(command) != 0)
	{
		printf("❌ Не вдалося змінити файл (очікувано).\n");
	}
	else
	{
		printf("✅ Файл змінено (неочікувано!)\n");
	}

	printf("4. Спроба видалити файл як звичайний користувач...\n");
	snprintf(command, sizeof(command), "rm %s", copiedfile);
	if (system(command) != 0)
	{
		printf("❌ Видалити не вдалося (можливо, немає прав на каталог).\n");
	}
	else
	{
		printf("✅ Файл видалено (каталог дозволяє видалення).\n");
	}

	return 0;
}
