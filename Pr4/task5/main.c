#include <stdio.h>
#include <stdlib.h>

void test_failed_realloc() {
    size_t initial_size = 1024;   
    size_t huge_size = (size_t)-1;  

    void *ptr = malloc(initial_size);
    if (!ptr) {
        printf("malloc не вдалося\n");
        return;
    }

    printf("malloc успішно: %p\n", ptr);

    void *tmp = realloc(ptr, huge_size); 

    if (!tmp) {
        printf("realloc не вдалося — памʼять залишилася у ptr: %p\n", ptr);
        free(ptr);  
    } else {
        printf("realloc вдалося (неочікувано): %p\n", tmp);
        free(tmp);
    }
}

int main() {
    test_failed_realloc();
    return 0;
}
