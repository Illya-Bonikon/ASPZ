#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void handle_signal(int sig)
{
	write(STDOUT_FILENO, "Signal caught\n", 14);
}

int main()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART; // автоматичне відновлення перерваних викликів
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);

	while (1)
	{
		pause(); // чекає на сигнал
	}

	return 0;
}
