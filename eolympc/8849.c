#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);

    int ones = n % 10;
    int tens = (n % 100 / 10);

  
    printf("%d", tens);
    printf("%d", tens);
      printf("%d", ones);
    printf("%d", ones);
}