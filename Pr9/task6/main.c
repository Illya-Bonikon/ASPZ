#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>

void run_ls(const char *path)
{
	printf("\n=== ls -l %s ===\n", path);
	char *args[] = {"ls", "-l", (char *)path, NULL};
	pid_t pid = fork();
	if (pid == 0)
	{
		execvp("ls", args);
		perror("execvp failed");
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

void try_access_file(const char *filepath)
{
	printf("\nФайл: %s\n", filepath);

	int fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		printf("  ❌ Читання: %s\n", strerror(errno));
	}
	else
	{
		printf("  ✅ Читання: доступ дозволено\n");
		close(fd);
	}

	fd = open(filepath, O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		printf("  ❌ Запис: %s\n", strerror(errno));
	}
	else
	{
		printf("  ✅ Запис: доступ дозволено\n");
		close(fd);
	}

	if (access(filepath, X_OK) == 0)
	{
		printf("  ✅ Виконання: доступ дозволено\n");
	}
	else
	{
		printf("  ❌ Виконання: %s\n", strerror(errno));
	}
}

void explore_directory(const char *dirpath, size_t max_files)
{
	DIR *dir = opendir(dirpath);
	if (!dir)
	{
		perror("Не вдалося відкрити директорію");
		return;
	}
	struct dirent *entry;
	size_t count = 0;

	while ((entry = readdir(dir)) != NULL && count < max_files)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		char filepath[1024];
		snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);

		struct stat st;
		if (stat(filepath, &st) == 0 && S_ISREG(st.st_mode))
		{
			try_access_file(filepath);
			count++;
		}
	}
	closedir(dir);
}

int main()
{
	const char *home = getenv("HOME");
	if (!home)
	{
		fprintf(stderr, "Не вдалося отримати домашній каталог\n");
		return 1;
	}

	run_ls(home);
	run_ls("/usr/bin");
	run_ls("/etc");

	printf("\n=== Перевірка доступу у домашньому каталозі ===\n");
	explore_directory(home, 5);

	printf("\n=== Перевірка доступу у /usr/bin ===\n");
	explore_directory("/usr/bin", 5);

	printf("\n=== Перевірка доступу у /etc ===\n");
	explore_directory("/etc", 5);

	return 0;
}
