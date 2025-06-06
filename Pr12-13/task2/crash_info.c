#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handler(int sig, siginfo_t *info, void *ucontext)
{
	printf("\n=== Detailed Crash Information ===\n");
	printf("Signal number: %d\n", sig);
	printf("Signal code: %d\n", info->si_code);
	printf("Fault address: %p\n", info->si_addr);
	printf("Process ID: %d\n", info->si_pid);
	printf("User ID: %d\n", info->si_uid);
	printf("Exit value: %d\n", info->si_status);

	// Додаткова інформація про тип помилки
	switch (sig)
	{
	case SIGSEGV:
		printf("Segmentation fault type: ");
		switch (info->si_code)
		{
		case SEGV_MAPERR:
			printf("Address not mapped to object\n");
			break;
		case SEGV_ACCERR:
			printf("Invalid permissions for mapped object\n");
			break;
		default:
			printf("Unknown\n");
		}
		break;
	case SIGFPE:
		printf("Floating point exception type: ");
		switch (info->si_code)
		{
		case FPE_INTDIV:
			printf("Integer divide by zero\n");
			break;
		case FPE_INTOVF:
			printf("Integer overflow\n");
			break;
		default:
			printf("Unknown\n");
		}
		break;
	}

	exit(1);
}

int main()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;

	// Реєстрація обробників
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);

	printf("Process started. PID: %d\n", getpid());
	printf("Press Enter to trigger a crash...\n");
	getchar();

	// Виклик помилки
	int *p = NULL;
	*p = 42; // Викликає SIGSEGV

	return 0;
}