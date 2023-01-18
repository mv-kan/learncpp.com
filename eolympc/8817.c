#include <stdio.h>

//https://www.eolymp.com/ru/submissions/12682583
int main() {
    int a = 0;
    scanf("%d", &a);

    printf("%c", '9');
    for (int i = 1; i < a; i++)
    {
        printf("0");
    }
    printf("\n");
}