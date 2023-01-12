#include <stdio.h> 
// #include <stdlib.h>
#include <malloc.h>
// #include <string.h>

// https://www.eolymp.com/ru/problems/5323
// https://www.eolymp.com/ru/submissions/12639254

typedef unsigned long long ull;

char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// converts char digit to decimal number 
int digitToDecimal(char digit) {
    char *findChar;
    int index;

    for (char* i = digits; *i != '\0'; i++)
    {
        if (*i == digit) {
            findChar = i;
            break;
        }
    }
    
    index = (int)(findChar - digits);

    return index;
}

// converts decimal num to digit
// must be less than 36 or more or equal 0
char decimalToDigit(int dec) {
    if (dec < 0 || dec > 36)
        return '?';
    return digits[dec]; 
}

ull convertFrom(char* num, ull numericalSystem) {
    int len = 0;
    // calc len without strlen
    for (char* i = num; *i != '\0'; i++)
    {
        len++;
    }
    
    ull result = 0;
    ull numericalDigit = 1;
    for (int i = len - 1; i >= 0; --i)
    {
        // convert num in numericalSystem to decimal 
        char digit = num[i];
        int decimal = digitToDecimal(digit);

        // multiply numerical digit on numerical system to get value in decimal
        result += numericalDigit * (ull)decimal;
        numericalDigit *= numericalSystem;
    }
    return result;
}

char* convertTo(ull decimal, ull numericalSystem) {
    // not good, but good enough
    // tmp is going to have converted number, but reversed
    char tmp[10000];
    ull resultLen = 0;

    for (ull n = decimal; n > 0; n /= numericalSystem)
    {
        // calc remain, and convert remain to char digit
        int remain = n % numericalSystem;
        char digit = decimalToDigit(remain);// digits[remain];

        // append char digit to the end of result string
        tmp[resultLen] = digit;
        resultLen++;
    }
    
    // reverse result string
    char* result = (char*)malloc((size_t)(resultLen + 1)); // + 1 for \0 character
    for (ull i = 0; i < resultLen; i++)
    {
        result[i] = tmp[resultLen - i - 1]; // - 1 because result len is not index it is size of @tmp
    }
    result[resultLen] = '\0';
    return result;
}

int main() {
    ull m = 0;
    ull k = 0;
    char A[1001];

    scanf("%llu", &m);
    scanf("%llu", &k);
    scanf("%s", A);

    // converting numbers
    ull AInDecimal = convertFrom(A, m);
    char* result = convertTo(AInDecimal, k);

    // printing result
    printf("%s\n", result);

    // free result, yes this comment was really helpful I know.
    free(result);
}