#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	// Маскуємо SIGINT
	sigprocmask(SIG_BLOCK, &set, NULL);
	printf("SIGINT заблоковано на 10 секунд. Спробуйте натиснути Ctrl+C...\n");

	sleep(10); // критична секція

	// Розблокуємо SIGINT
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	printf("SIGINT розблоковано. Тепер Ctrl+C завершить програму.\n");

	// Очікуємо сигнал
	while (1)
	{
		sleep(1);
	}

	return 0;
}
