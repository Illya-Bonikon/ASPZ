#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long get_time_ms() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000L + t.tv_usec / 1000L;
}

int main() {
    long start, end;
    
    start = get_time_ms();

    for (volatile long i = 0; i < 100000000; i++); 

    end = get_time_ms();

    printf("Час виконання: %ld мс\n", end - start);

    return 0;
}
