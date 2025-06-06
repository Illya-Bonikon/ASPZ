#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void handler(int sig)
{
	time_t now = time(NULL);
	struct tm *tm_info = localtime(&now);
	char buf[64];
	strftime(buf, sizeof(buf), "%H:%M:%S\n", tm_info);
	write(STDOUT_FILENO, buf, strlen(buf));

	// перезапускаємо таймер ще на 1 секунду
	alarm(1);
}

int main()
{
	// Встановлюємо обробник сигналу
	signal(SIGALRM, handler);

	// Запускаємо таймер уперше
	alarm(1);

	// Нескінченний цикл очікування сигналів
	while (1)
	{
		pause(); // чекаємо на сигнал
	}

	return 0;
}
