#include <stdio.h>
#include <limits.h>

int main() {
    printf("Signed Char Limits: %+d - %+d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned Char Limits: %u - %u\n", 0, UCHAR_MAX);

    printf("Signed Short Limits: %+d - %+d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned Short Limits: %u - %u\n", 0, USHRT_MAX);

    printf("Signed Int Limits: %+d - %+d\n", INT_MIN, INT_MAX);
    printf("Unsigned Int Limits: %u - %u\n", 0, UINT_MAX);
}
