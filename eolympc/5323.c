#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

// 5323

char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// converts char digit to decimal number 
int digitToDecimal(char digit) {
    char *findChar;
    int index;

    findChar = strchr(digits, digit);
    index = (int)(findChar - digits);

    return index;
}

// converts decimal num to digit
// must be less than 36 or more or equal 0
char decimalToDigit(int dec) {
    if (dec < 0 || dec > 36)
        exit(1);
    return digits[dec]; 
}

int convertFrom(char* num, int numericalSystem) {
    int len = strlen(num);
    int result = 0;
    int numericalDigit = 1;
    for (int i = len - 1; i >= 0; --i)
    {
        // convert num in numericalSystem to decimal 
        char digit = num[i];
        int decimal = digitToDecimal(digit);

        // multiply numerical digit on numerical system to get value in decimal
        result += numericalDigit * decimal;
        numericalDigit *= numericalSystem;
    }
    return result;
}

char* convertTo(int decimal, int numericalSystem) {
    // not good, but good enough
    // tmp is going to have converted number, but reversed
    char tmp[1000];
    int resultLen = 0;

    for (int n = decimal; n > 0; n /= numericalSystem)
    {
        // calc remain, and convert remain to char digit
        int remain = n % numericalSystem;
        char digit = digits[remain];

        // append char digit to the end of result string
        tmp[resultLen] = digit;
        resultLen++;
    }
    
    // reverse result string
    char* result = malloc((size_t)(resultLen + 1)); // + 1 for \0 character
    for (int i = 0; i < resultLen; i++)
    {
        result[i] = tmp[resultLen - i - 1]; // - 1 because result len is not index it is size of @tmp
    }
    result[resultLen] = '\0';
    return result;
}

int main() {
    int n = 0;
    char A[1000];
    int k = 0;

    scanf("%d", &n);
    scanf("%s", A);
    scanf("%d", &k);
    // converting numbers
    int AInDecimal = convertFrom(A, n);
    char* result = convertTo(AInDecimal, k);

    // printing result
    printf("%s", result);

    // free result, yes this comment was really helpful I know.
    free(result);
}