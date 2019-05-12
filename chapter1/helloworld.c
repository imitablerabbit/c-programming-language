#include <stdio.h>

int main()
{
    printf("hello world!\n");
    printf("hello world!\t\n");
    printf("hello world!\b\n");
    printf("hello world!\a\n");

    // Exercise 1-2 looks like it complains when it does not recognise the
    // character code. It will then print out the unescaped character instead
    printf("hello world!\c\n");
    printf("hello world!\d\n");
    printf("hello world!\e\n");
    printf("hello world!\f\n");
}
