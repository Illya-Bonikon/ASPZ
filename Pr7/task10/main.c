#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float random_float_0_1() {
    return (float)rand() / (float)RAND_MAX;
}

float random_float_0_n(float n) {
    return random_float_0_1() * n;
}

int main() {
    float n;
    int count = 5;

    srand((unsigned int)time(NULL));

    printf("Введіть n (дійсне число > 0): ");
    if (scanf("%f", &n) != 1 || n <= 0.0f) {
        fprintf(stderr, "Некоректне значення n\n");
        return 1;
    }

    printf("\n(a) Випадкові числа в діапазоні [0.0, 1.0]:\n");
    for (int i = 0; i < count; ++i)
        printf("%.5f\n", random_float_0_1());

    printf("\n(b) Випадкові числа в діапазоні [0.0, %.2f]:\n", n);
    for (int i = 0; i < count; ++i) 
        printf("%.5f\n", random_float_0_n(n));
    

    return 0;
}
