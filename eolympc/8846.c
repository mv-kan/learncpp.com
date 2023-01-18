#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int ones = n % 10 * 10;
    int tens = (n % 100 / 10);
    n /= 100;
    n *= 100;
    n = (n + ones + tens);
    printf("%d", n);
}