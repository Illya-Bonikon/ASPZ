#include <stdio.h>

void func()
{
	int array1[10000];
	int array2[10000];
	printf("Stack top after allocation: %p\n", &array2);
}

int main()
{
	int i;
	printf("Initial stack top:          %p\n", &i);
	func();
	return 0;
}