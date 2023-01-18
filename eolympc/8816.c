#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12682507
int main() {
    size_t a = 0;
    size_t n = 0;
    scanf("%zu\n", &a);
    scanf("%zu", &n);

    size_t result = 1;
    for (size_t i = 0; i < n; i++)
    {
        result *= a;
    }
    printf("%zu", result);
}