#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int sig, siginfo_t *info, void *ctx)
{
	printf("🔔 Отримано сигнал %d з даними: %d (від PID %d)\n",
		   sig, info->si_value.sival_int, info->si_pid);
}

int main()
{
	struct sigaction sa = {0};
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGRTMIN, &sa, NULL);

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return 1;
	}
	else if (pid == 0)
	{
		// Дочірній процес — надсилає сигнал
		sleep(1); // даємо батькові час зареєструвати обробник
		union sigval val;
		val.sival_int = 1337;
		if (sigqueue(getppid(), SIGRTMIN, val) == -1)
		{
			perror("sigqueue");
			exit(1);
		}
		printf("👶 Дочірній: сигнал відправлено!\n");
		exit(0);
	}
	else
	{
		// Батьківський процес — чекає сигналу
		printf("👨 Батько: PID = %d, чекаю сигналу...\n", getpid());
		pause();
		wait(NULL); // дочекаємося завершення дочірнього
	}

	return 0;
}
