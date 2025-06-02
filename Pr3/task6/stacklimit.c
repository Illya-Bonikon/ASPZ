#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void recurse(int depth)
{
	char arr[1024];
	printf("Глибина: %d\n", depth);
	recurse(depth + 1);
}

int main()
{
	struct rlimit rl;
	rl.rlim_cur = 8192; // 8 КБ
	rl.rlim_max = 8192;
	setrlimit(RLIMIT_STACK, &rl);
	recurse(1);
	return 0;
}