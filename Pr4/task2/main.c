#include <stdio.h>
#include <stdlib.h>

void try_malloc_with_size(size_t size)
{
	printf("Спроба виділити памʼять: %zu байт\n", size);

	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("malloc не вдалося виділити памʼять.\n");
	}
	else
	{
		printf("malloc виділив памʼять!\n");
		free(ptr);
	}

	printf("------\n");
}

void test_overflowed_signed_multiplication()
{
	int xa = 1 << 16; // 65536
	int xb = 1 << 16; // 65536

	int num = xa * xb; // очікуване: 4294967296 -> переповнення int -> результат = 0

	printf("xa = %d, xb = %d, num (xa * xb) = %d (очікуване переповнення)\n", xa, xb, num);
	try_malloc_with_size((size_t)num);
}

void test_negative_malloc()
{
	int negative_size = -100;
	printf("Передаємо у malloc відʼємне значення: %d\n", negative_size);
	try_malloc_with_size((size_t)negative_size);
}

int main()
{

	// test_negative_malloc();
	// test_overflowed_signed_multiplication();

	return 0;
}
