#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024

int main()
{
	char line[MAX];

	while (1)
	{
		printf("dumbsh> ");
		if (!fgets(line, MAX, stdin))
			break;

		line[strcspn(line, "\n")] = 0; // Видаляємо символ нового рядка

		if (strcmp(line, "exit") == 0)
			break;

		pid_t pid = fork();
		if (pid == 0)
		{
			execlp(line, line, NULL); // Замінюємо поточний процес
			perror("exec failed");	  // Якщо exec не виконався
			exit(1);
		}
		else
		{
			wait(NULL); // Очікуємо завершення дочірнього процесу
		}
	}

	return 0;
}
