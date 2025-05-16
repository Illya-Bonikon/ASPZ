#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <jemalloc/jemalloc.h>

void* my_malloc(size_t size) {
    return je_malloc(size);
}

void benchmark(void* (*alloc_func)(size_t), const char *name, size_t iterations, size_t size) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t i = 0; i < iterations; i++) {
        void *p = alloc_func(size);
        if (!p) {
            fprintf(stderr, "%s: не вдалося виділити пам'ять\n", name);
            break;
        }
        free(p);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("%s: Виділення і звільнення %zu разів по %zu байт зайняло %.6f секунд\n", name, iterations, size, elapsed);
}

int main() {
    size_t iterations = 1000000;
    size_t size = 64;

    benchmark(malloc, "Стандартний malloc", iterations, size);
    benchmark(my_malloc, "jemalloc через my_malloc", iterations, size);

    return 0;
}
