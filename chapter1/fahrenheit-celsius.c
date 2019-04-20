#include <stdio.h>

float fahrtocel(float);

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = -20;

    fahr = upper;
    printf("Fahrenheit\tCelsius\n");
    while (fahr >= lower) {
        celsius = fahrtocel(fahr);
        printf("%10.0f\t%7.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

// Convert celsius to fahrenheit
float fahrtocel(float fahr) {
    return 5.0/9.0 * (fahr - 32.0);
}
