#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

void print_permissions(mode_t mode)
{
	char types[] = {'-', 'd', 'l', 'c', 'b', 's', 'p'};
	char type_char = '-';

	if (S_ISREG(mode))
		type_char = '-';
	else if (S_ISDIR(mode))
		type_char = 'd';
	else if (S_ISLNK(mode))
		type_char = 'l';
	else if (S_ISCHR(mode))
		type_char = 'c';
	else if (S_ISBLK(mode))
		type_char = 'b';
	else if (S_ISSOCK(mode))
		type_char = 's';
	else if (S_ISFIFO(mode))
		type_char = 'p';

	printf("%c", type_char);

	printf((mode & S_IRUSR) ? "r" : "-");
	printf((mode & S_IWUSR) ? "w" : "-");
	printf((mode & S_IXUSR) ? "x" : "-");
	printf((mode & S_IRGRP) ? "r" : "-");
	printf((mode & S_IWGRP) ? "w" : "-");
	printf((mode & S_IXGRP) ? "x" : "-");
	printf((mode & S_IROTH) ? "r" : "-");
	printf((mode & S_IWOTH) ? "w" : "-");
	printf((mode & S_IXOTH) ? "x" : "-");
}

int main()
{
	DIR *dir = opendir(".");
	if (!dir)
	{
		perror("opendir failed");
		return 1;
	}

	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
	{
		struct stat st;
		if (stat(entry->d_name, &st) == -1)
		{
			perror("stat failed");
			continue;
		}

		print_permissions(st.st_mode);
		printf(" ");

		printf("%ld ", (long)st.st_nlink);

		struct passwd *pw = getpwuid(st.st_uid);
		struct group *gr = getgrgid(st.st_gid);

		printf("%s %s ", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");

		printf("%5lld ", (long long)st.st_size);

		char timebuf[64];
		struct tm *tm_info = localtime(&st.st_mtime);
		strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
		printf("%s ", timebuf);

		printf("%s\n", entry->d_name);
	}

	closedir(dir);
	return 0;
}
