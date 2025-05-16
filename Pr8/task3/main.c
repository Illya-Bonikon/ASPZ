#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


bool is_sorted(int *arr, size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i-1] > arr[i]) return false;
    }
    return true;
}


void generate_array(int *arr, size_t n, int type) {
    switch(type) {
        case 0: 
            for (size_t i = 0; i < n; i++) arr[i] = rand() % 10000;
            break;
        case 1: 
            for (size_t i = 0; i < n; i++) arr[i] = i;
            break;
        case 2: 
            for (size_t i = 0; i < n; i++) arr[i] = n - i;
            break;
        case 3: 
            for (size_t i = 0; i < n; i++) arr[i] = 42;
            break;
        case 4: 
            for (size_t i = 0; i < n/2; i++) arr[i] = i;
            for (size_t i = n/2; i < n; i++) arr[i] = rand() % 10000;
            break;
    }
}


double benchmark(int *arr, size_t n) {
    clock_t start = clock();
    qsort(arr, n, sizeof(int), compare_ints);
    clock_t end = clock();

    if (!is_sorted(arr, n)) {
        fprintf(stderr, "Помилка: масив не відсортовано!\n");
        exit(EXIT_FAILURE);
    }

    return (double)(end - start) / CLOCKS_PER_SEC;
}


void run_tests() {
    printf("Тестування qsort...\n");

    
    int empty[0];
    qsort(empty, 0, sizeof(int), compare_ints);

    
    int one[1] = {5};
    qsort(one, 1, sizeof(int), compare_ints);
    if (one[0] != 5) printf("Тест на один елемент провалено\n");

    
    int same[5] = {7,7,7,7,7};
    qsort(same, 5, sizeof(int), compare_ints);
    if (!is_sorted(same, 5)) printf("Тест на однакові елементи провалено\n");

    printf("Усі базові тести пройдені\n");
}


void find_worst_cases(size_t n) {
    int *arr = malloc(n * sizeof(int));
    int *copy = malloc(n * sizeof(int));

    const char *types[] = {
        "Випадковий",
        "Вже відсортований",
        "Відсортований у зворотному порядку",
        "Однакові елементи",
        "Частково відсортований"
    };

    for (int t = 0; t < 5; t++) {
        generate_array(arr, n, t);
        memcpy(copy, arr, n * sizeof(int));
        double time = benchmark(copy, n);
        printf("%s масив: час сортування %.6f секунд\n", types[t], time);
    }

    free(arr);
    free(copy);
}

int main() {
    srand(time(NULL));

    run_tests();

    size_t n = 100000; 
    printf("Запуск дослідження для масиву розміром %zu\n", n);
    find_worst_cases(n);

    return 0;
}
