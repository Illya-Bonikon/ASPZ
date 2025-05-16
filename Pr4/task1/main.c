#include <stdio.h>
#include <stdlib.h>

int main() {
size_t size = (size_t)-1;
    printf("Максимальне size_t: %zu\n", size);

    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("malloc не вдалося виділити пам'ять.\n");
    } else {
        printf("malloc виділив пам'ять!\n");
        free(ptr);
    }
    return 0;
}
