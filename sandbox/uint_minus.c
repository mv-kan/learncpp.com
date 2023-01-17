#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {

    size_t a = 5;
    size_t b = 10;
    size_t c = a - b - a; // -5
    size_t d = 100 + c ; // 95
    printf("%zu", d); 
}