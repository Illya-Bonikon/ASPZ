#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <signal.h>
#include <unistd.h>

void cpu_limit_handler(int signum)
{
	printf("Ліміт часу ЦП вичерпано!\n");
	exit(1);
}

void generate_unique(int *arr, int count, int max)
{
	int i = 0;
	while (i < count)
	{
		int num = rand() % max + 1;
		int unique = 1;
		for (int j = 0; j < i; ++j)
		{
			if (arr[j] == num)
			{
				unique = 0;
				break;
			}
		}
		if (unique)
			arr[i++] = num;
	}
}

int main()
{
	struct rlimit rl;
	rl.rlim_cur = 1; // 1 секунда
	rl.rlim_max = 1;
	setrlimit(RLIMIT_CPU, &rl);
	signal(SIGXCPU, cpu_limit_handler);
	srand(time(NULL));
	int lotto1[7], lotto2[6];
	generate_unique(lotto1, 7, 49);
	generate_unique(lotto2, 6, 36);
	printf("7 із 49: ");
	for (int i = 0; i < 7; ++i)
		printf("%d ", lotto1[i]);
	printf("\n6 із 36: ");
	for (int i = 0; i < 6; ++i)
		printf("%d ", lotto2[i]);
	printf("\n");
	return 0;
}