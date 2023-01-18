#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int tmp = n % 100 * 10;
    n /= 1000;
    n *= 1000;
    n = (n + tmp) / 10;
    printf("%d", n);
}