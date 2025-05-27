
#include <stdlib.h>

int main() {
    int *arr = malloc(10 * sizeof(int));
    arr[10] = 5;  
    return 0;     
}

// gcc -fsanitize=address -g -o leak_asan leak.c
// ./leak_val

// gcc -g -o leak_val leak.c
// valgrind ./leak_val
