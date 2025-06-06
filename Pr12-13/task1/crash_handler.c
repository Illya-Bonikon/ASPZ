#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void cleanup_resources()
{
	printf("Cleaning up resources...\n");
	// Тут можна додати очищення файлів, сокетів тощо
}

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	printf("\n=== Crash Information ===\n");
	printf("Signal: %d (%s)\n", sig, strsignal(sig));
	printf("Fault address: %p\n", info->si_addr);
	printf("Process ID: %d\n", getpid());

	// Очищення ресурсів перед завершенням
	cleanup_resources();

	// Завершення процесу
	exit(1);
}

int main()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;

	// Реєстрація обробників для різних сигналів
	sigaction(SIGSEGV, &sa, NULL); // Сегментаційна помилка
	sigaction(SIGFPE, &sa, NULL);  // Ділення на нуль
	sigaction(SIGILL, &sa, NULL);  // Незаконна інструкція
	sigaction(SIGBUS, &sa, NULL);  // Помилка шини

	printf("Process started. PID: %d\n", getpid());
	printf("Press Enter to trigger different crashes...\n");
	getchar();

	// Демонстрація різних типів помилок
	printf("1. Triggering SIGSEGV...\n");
	int *ptr = NULL;
	*ptr = 42; // Викликає SIGSEGV

	printf("2. Triggering SIGFPE...\n");
	int a = 1, b = 0;
	int c = a / b; // Викликає SIGFPE

	return 0;
}