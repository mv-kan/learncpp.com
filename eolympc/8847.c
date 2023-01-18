#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int ones = n % 10 * 100;
    int tens = (n % 100 / 10) * 10;
    int hundreds = (n % 1000 / 100);
    n /= 1000;
    n *= 1000;
    n = (n + ones + hundreds + tens);
    printf("%d", n);
}