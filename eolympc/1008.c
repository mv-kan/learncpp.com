#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/*
100100

module by 2^8 (one byte) and you get decimal for first byte

devide by 2^8 (one byte) and you get decimal for second byte

*/

#define MAX_CHARS 10000
#define MAX_CHARS_INPUT 1001
#define BYTE_SIZE 2000
#define BYTE_MAX 256

typedef unsigned char byte;
typedef unsigned long long ull;

char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// converts char digit to decimal number
int digitToDecimal(char digit)
{
    char *findChar;
    int index;

    findChar = strchr(digits, digit);
    index = (int)(findChar - digits);

    return index;
}

// converts decimal num to digit
// must be less than 36 or more or equal 0
char decimalToDigit(int dec)
{
    if (dec < 0 || dec > 36)
        exit(1);
    return digits[dec];
}

/*
get last valid byte for @num
@num is number that is from bytes
*/
int getLastByte(byte *num)
{
    for (int i = BYTE_SIZE; i >= 0; --i)
    {
        if (num[i] != 0)
        {
            return i;
        }
    }
    return 0;
}

// get num that is least significant endian
byte *toBytes(char *num, int numericalSystem)
{
    // byte* bytenum = new byte[BYTE_SIZE];// cpp
    byte *bytenum = (byte*)malloc(BYTE_SIZE * sizeof(byte)); // c
    int iBytenum = 0;

    int len = strlen(num);
    ull result = 0;
    ull numericalDigit = 1;
    for (int i = len - 1; i >= 0; --i)
    {
        // convert num in numericalSystem to decimal
        char digit = num[i];
        int decimal = digitToDecimal(digit);

        // multiply numerical digit on numerical system to get value in decimal
        result += (ull)(numericalDigit * (ull)decimal);
        numericalDigit *= (ull)numericalSystem;
        
        
        // if result is bigger than BYTE_MAX (2^8)
        // dump all result 256 chunks into @bytenum
        // OR
        // if this is last iteration and result bigger than zero (then we have some values to save)
        // BUG!!! if number is very big like 10000000000000000000000000000000
        // with zeros this will completely broke, because result cannot hold that value
        // we just hope that we will not encounter more consequent zeros than unsigned long long
        while (result > BYTE_MAX || (i - 1 < 0 && result > 0))
        {
            // we put the value to byte
            bytenum[iBytenum] = result % BYTE_MAX;
            // increment iBytenum to set it to empty byte in @bytenum
            iBytenum++;
            // devide result
            result /= BYTE_MAX;
            // and reset numerical digit
            numericalDigit = 1;
        }
        
    }
    return bytenum;
}

char *convertTo(byte *num, int numericalSystem)
{
    // not good, but good enough
    // tmp is going to have converted number, but reversed
    char tmp[1000];
    int tmpLen = 0;
    int size = getLastByte(num) + 1;
    ull sumOfBytes = 0;
    for (int i = 0; i < size; i++)
    {
        sumOfBytes += num[i];
        // if sumOfBytes bigger than numericalSystem
        // OR
        // if it is last iteration and sumOfBytes bigger than zero (some stuff to save)
        while (sumOfBytes > (ull)numericalSystem || (i + 1 == size && sumOfBytes > 0))
        {
            // calc remain, and convert remain to char digit
            int remain = sumOfBytes % (ull)numericalSystem;
            char digit = digits[remain];

            // append char digit to the end of result string
            tmp[tmpLen] = digit;
            tmpLen++;

            // divide sumOfBytes because we used for remains it 
            sumOfBytes /= (ull)numericalSystem;
        }
    }

    // reverse result string
    char *result = (char*)malloc((size_t)(tmpLen + 1)); // + 1 for \0 character
    for (int i = 0; i < tmpLen; i++)
    {
        result[i] = tmp[tmpLen - i - 1]; // - 1 because result len is not index it is size of @tmp
    }
    result[tmpLen] = '\0';
    return result;
}

void printBytes(byte* num) {
    int size = getLastByte(num)+ 1;
    for (int i = 0; i < size; i++)
    {
        printf("%d ", num[i]);
    }
    printf("\n");
}

int main()
{
    int m = 0;
    int k = 0;
    char n[MAX_CHARS_INPUT];

    scanf("%d %d", &m, &k);
    scanf("%s", n);

    // convert input number to bytes representation
    byte* num = toBytes(n, m);
    printBytes(num);
    char* result = convertTo(num, k);

    printf("%s\n", result);

    free(result);
    free(num);
    return 0;
}