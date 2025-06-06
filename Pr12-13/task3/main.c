#include <signal.h>
#include <stdio.h>

void handle_sigint(int sig)
{
	printf("Caught signal %d\n", sig);
}

int main()
{
	signal(SIGINT, handle_sigint); // обробка Ctrl+C
	while (1)
	{
	} // нескінченний цикл
}
