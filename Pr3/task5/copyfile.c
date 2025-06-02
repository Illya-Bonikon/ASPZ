#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Program need two arguments\n");
		return 1;
	}
	FILE *src = fopen(argv[1], "rb");
	if (!src)
	{
		printf("Cannot open file %s for reading\n", argv[1]);
		return 1;
	}
	FILE *dst = fopen(argv[2], "wb");
	if (!dst)
	{
		printf("Cannot open file %s for writing\n", argv[2]);
		fclose(src);
		return 1;
	}
	struct rlimit rl;
	rl.rlim_cur = 100; // 100 байт
	rl.rlim_max = 100;
	setrlimit(RLIMIT_FSIZE, &rl);
	char buf[32];
	size_t n;
	while ((n = fread(buf, 1, sizeof(buf), src)) > 0)
	{
		if (fwrite(buf, 1, n, dst) < n)
		{
			if (errno == EFBIG)
			{
				printf("Досягнуто ліміту розміру файлу!\n");
			}
			else
			{
				printf("Помилка запису!\n");
			}
			break;
		}
	}
	fclose(src);
	fclose(dst);
	return 0;
}