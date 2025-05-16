#include <stdio.h>
#include <stdlib.h>

#define CYCLES 3

void incorrect_usage(size_t n) {
    printf("\nIncorrect_usage:\n");
    void *ptr = NULL;

    for (int i = 0; i < CYCLES; i++) {
        if (!ptr)
            ptr = malloc(n);  

        if (!ptr) {
            printf("malloc не вдалося на ітерації %d\n", i);
            return;
        }

        printf("malloc -> %p на ітерації %d\n", ptr, i);


        free(ptr);    
    }
}

void correct_usage(size_t n) {
    printf("\nCorrect_usage:\n");
    void *ptr = malloc(n);

    if (!ptr) {
        printf("malloc не вдалося\n");
        return;
    }

    for (int i = 0; i < CYCLES; i++) {
        printf("Використання одного і того ж ptr -> %p на ітерації %d\n", ptr, i);
    }

    free(ptr);  
}

int main() {
    size_t n = 32;

    // incorrect_usage(n); 
    // correct_usage(n);   

    return 0;
}
