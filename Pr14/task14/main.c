#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>

void set_raw_mode(int enable)
{
	static struct termios oldt;
	struct termios newt;

	if (enable)
	{
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
}

volatile sig_atomic_t start_flag = 0;
struct timespec start_time, end_time;

void signal_handler(int sig, siginfo_t *si, void *uc)
{
	printf("\n🚦 Натисни будь-яку клавішу!\n");
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	start_flag = 1;
}

int main()
{
	printf("Гра на реакцію\n");
	printf("Після випадкової затримки з'явиться повідомлення.\n");
	printf("Натисніть клавішу якомога швидше!\n");
	printf("Готові? Тоді натисніть Enter, i хай почнеться гра...\n");
	getchar();

	struct sigaction sa = {0};
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGRTMIN, &sa, NULL);

	timer_t timerid;
	struct sigevent sev = {0};
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	timer_create(CLOCK_REALTIME, &sev, &timerid);

	srand(time(NULL));
	int delay = 1 + rand() % 5;

	struct itimerspec its = {0};
	its.it_value.tv_sec = delay;
	its.it_value.tv_nsec = 0;
	timer_settime(timerid, 0, &its, NULL);

	set_raw_mode(1);

	while (1)
	{
		if (start_flag && getchar())
		{
			clock_gettime(CLOCK_MONOTONIC, &end_time);
			break;
		}
	}

	set_raw_mode(0);

	timer_delete(timerid);

	long diff_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 +
				   (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

	printf("Ваш час реакції: %ld мс\n", diff_ms);
	return 0;
}
