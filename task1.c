#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main () {
    time_t t = 1;
    while(t>0) 
        t++;
    t--;
    printf("time_t will overflow at: %s\n", ctime(&t));

    printf("Size of time_t: %zu bytes\n", sizeof(time_t));
    if (sizeof(time_t) == 4)
        printf("Size of 32bit\n");
    else if (sizeof(time_t) == 8)
        printf("Size of 64bit\n");
    else
        printf ("unexpected size\n");
    return 0;
}

