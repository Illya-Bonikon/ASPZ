#include <stdio.h>
#include <stdlib.h>

void test_realloc_null()
{
	printf("=== realloc(NULL, size) ===\n");
	void *p = realloc(NULL, 64);
	if (p)
	{
		printf("malloc через realloc: %p\n", p);
		free(p);
	}
	else
	{
		printf("malloc через realloc не вдалося\n");
	}
}

void test_realloc_zero()
{
	printf("\n=== realloc(ptr, 0) ===\n");
	void *p = malloc(64);
	if (!p)
	{
		printf("malloc не вдалося\n");
		return;
	}
	printf("malloc: %p\n", p);

	void *q = realloc(p, 0);
	printf("realloc(ptr, 0) повернув: %p\n", q);

	if (q)
		free(q);
	else
		printf("Пам'ять вже звільнена realloc-ом\n");
}

int main()
{
	test_realloc_null();
	test_realloc_zero();
	return 0;
}
