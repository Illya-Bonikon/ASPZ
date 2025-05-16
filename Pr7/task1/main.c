#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;

	fp = popen("rwho | more", "r");
	if (fp == NULL)
	{
		perror("popen failed");
		return 1;
	}

	char buffer[256];
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		fputs(buffer, stdout);
	}

	int status = pclose(fp);
	if (status == -1)
	{
		perror("pclose failed");
		return 1;
	}
	else
	{
		printf("\nКоманда завершилась зі статусом %d\n", status);
	}

	return 0;
}
