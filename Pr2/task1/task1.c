#include <stdio.h>
#include <time.h>
#include <stdint.h>

// 1.	Напишіть програму для визначення моменту, коли time_t закінчиться.
// Дослідіть, які зміни відбуваються в залежності від 32- та 64-бітної архітектури. 
// Дослідіть сегменти виконуваного файлу.

int main () {
    time_t time = 1;
    while(time>0) 
        time++;
    time--;
    printf("time_t will overflow at: %s\n", ctime(&time));

    printf("Size of time_t: %zu bytes\n", sizeof(time_t));
    if (sizeof(time_t) == 4)
        printf("Size of 32bit\n");
    else if (sizeof(time_t) == 8)
        printf("Size of 64bit\n");
    else
        printf ("unexpected size\n");
    return 0;
}

