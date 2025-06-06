#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <PID> <int_data>\n", argv[0]);
		return 1;
	}

	pid_t pid = atoi(argv[1]);
	int data = atoi(argv[2]);

	union sigval val;
	val.sival_int = data;

	if (sigqueue(pid, SIGRTMIN, val) == -1)
	{
		perror("sigqueue");
		return 1;
	}

	printf("Sent signal SIGRTMIN with data %d to PID %d\n", data, pid);
	return 0;
}
