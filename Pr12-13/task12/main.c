#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

void handler(int sig, siginfo_t *info, void *context)
{
	ucontext_t *uc = (ucontext_t *)context;
#if defined(__x86_64__)
	printf("Caught signal %d\n", sig);
	printf("Fault address: %p\n", info->si_addr);
	printf("RIP (instruction pointer): 0x%llx\n",
		   (unsigned long long)uc->uc_mcontext.gregs[REG_RIP]);
	printf("RSP (stack pointer):       0x%llx\n",
		   (unsigned long long)uc->uc_mcontext.gregs[REG_RSP]);
	printf("RAX (accumulator):         0x%llx\n",
		   (unsigned long long)uc->uc_mcontext.gregs[REG_RAX]);
#endif
	_exit(1); // завершити безпечним шляхом
}

int main()
{
	struct sigaction sa = {0};
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	int *p = NULL;
	*p = 123; // викличе SIGSEGV
}