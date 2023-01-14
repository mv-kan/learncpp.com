#include <stdio.h>
#include <string.h>

int main()
{
    char str1[15];
    char str2[15];

    memcpy(str1, "abcdef", 6);
    memcpy(str2, "ABCDEF", 6);

    str1[2] >>= 1;
    printf("%s\n", str1);

    return (0);
}