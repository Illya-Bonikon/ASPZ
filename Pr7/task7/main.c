#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int is_executable(const struct stat *sb)
{
	return (sb->st_mode & S_IXUSR) && S_ISREG(sb->st_mode);
}

void add_read_permission(const char *filename)
{
	struct stat sb;
	if (stat(filename, &sb) == 0)
	{
		mode_t new_mode = sb.st_mode | S_IROTH;
		if (chmod(filename, new_mode) == 0)
		{
			printf("Додано дозвіл на читання: %s\n", filename);
		}
		else
		{
			perror("Не вдалося змінити права доступу");
		}
	}
}

int main()
{
	DIR *dir;
	struct dirent *entry;
	struct stat sb;
	char answer[4];

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return 1;
	}

	printf("🔍 Пошук вихідних C-програм...\n");

	while ((entry = readdir(dir)) != NULL)
	{
		if (stat(entry->d_name, &sb) == 0 && is_executable(&sb))
		{
			printf("Знайдено: %s\n", entry->d_name);
			printf("Надати дозвіл на читання іншим (y/n)? ");
			fgets(answer, sizeof(answer), stdin);

			if (answer[0] == 'y' || answer[0] == 'Y')
			{
				add_read_permission(entry->d_name);
			}
		}
	}

	closedir(dir);
	return 0;
}
