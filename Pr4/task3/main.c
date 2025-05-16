#include <stdio.h>
#include <stdlib.h>

void test_malloc_zero() {
    printf("Спроба викликати malloc(0)...\n");

    void* ptr = malloc(0);

    if (ptr == NULL) {
        printf("malloc(0) повернув NULL\n");
    } else {
        printf("malloc(0) повернув не-NULL: %p\n", ptr);
        free(ptr);  
        printf("free(ptr) виконано\n");
    }

    printf("------\n");
}

int main() {
    test_malloc_zero();
    return 0;
}
