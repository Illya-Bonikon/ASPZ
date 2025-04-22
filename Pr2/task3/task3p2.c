#include <stdio.h>
#include <stdlib.h>

// Знайдіть розташування сегментів даних і тексту, а також купи всередині сегмента даних, оголосіть змінні, які будуть поміщені в ці сегменти, і виведіть їхні адреси.
int global_initialized = 42;
int global_uninitialized;

static int static_initialized = 100;
static int static_uninitialized;

void my_function() {}

int main()
{

	int local_var = 10;

	int *heap_var = (int *)malloc(sizeof(int));
	*heap_var = 99;

	printf("Address for function (text segment):            %p\n", (void *)my_function);
	printf("Address for global_initialized (.data):         %p\n", (void *)&global_initialized);
	printf("Address for global_uninitialized (.bss):        %p\n", (void *)&global_uninitialized);
	printf("Address for static_initialized (.data):         %p\n", (void *)&static_initialized);
	printf("Address for static_uninitialized (.bss):        %p\n", (void *)&static_uninitialized);
	printf("Address for local varriable (stack):            %p\n", (void *)&local_var);
	printf("Address for dynamic variable (heap) :           %p\n", (void *)heap_var);

	free(heap_var);

	return 0;
}
