#include <stdio.h>

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 100;
    step = 10;

    celsius = lower;
    printf("Celsius\tFahrenheit\n");
    while (celsius <= upper) {
        fahr = (celsius * 9.0/5.0) + 32;
        printf("%7.0f\t%10.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
