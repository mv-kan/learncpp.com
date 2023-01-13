#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/*
100100

module by 2^8 (one byte) and you get decimal for first byte

devide by 2^8 (one byte) and you get decimal for second byte

столбик

*/

#define MAX_CHARS 10000
#define MAX_CHARS_INPUT 1001
#define BYTE_SIZE 2000 // this is huge long t size
#define HUGE_LONG_T_SIZE BYTE_SIZE
#define BYTE_MAX 256
#define BYTE_T_MAX 256
#define BYTE_T_MAX_VALUE 255
typedef unsigned char byte_t;
// has size of HUGE_LONG_T_SIZE
// typedef byte* huge_long_t;

// least significant endian
struct huge_long_t
{
    size_t size;
    byte_t *bytes;
};

huge_long_t huge_long_t_make_zero(const size_t size)
{
    huge_long_t num;
    num.bytes = (byte_t *)malloc(size * sizeof(byte_t));
    num.size = size;
    memset(num.bytes, 0, size);
    return num;
}

huge_long_t huge_long_t_from_int(int integer) // int not const because we use this variable for calculation
{
    huge_long_t num = huge_long_t_make_zero(sizeof(int));
    int ibytes = 0;
    while (integer > 0)
    {
        // we put the value to byte
        num.bytes[ibytes] = integer % BYTE_T_MAX;
        // increment iBytenum to set it to empty byte in @bytenum
        ibytes++;
        // devide result
        integer /= BYTE_T_MAX;
    }
    return num;
}

void huge_long_t_delete(const huge_long_t *const num)
{
    if (num->bytes)
        free(num->bytes);
}

bool huge_long_t_is_zero(const huge_long_t num)
{
    for (size_t i = 0; i < num.size; i++)
    {
        if (num.bytes[i] != 0)
            return false;
    }
    return true;
}

huge_long_t huge_long_t_copy(const huge_long_t num)
{
    huge_long_t num_copy = huge_long_t_make_zero(num.size);
    for (size_t i = 0; i < num.size; i++)
    {
        num_copy.bytes[i] = num.bytes[i];
    }
    return num_copy;
}

void huge_long_t_add_assign(huge_long_t *const a, const huge_long_t b)
{
    if (a->size != b.size)
    {
        printf("a.size != b.size");
        exit(1);
    }

    int carry = 0;
    for (size_t i = 0; i < a->size; i++)
    {
        // sum cannot be bigger than 255 + 255
        int sum = a->bytes[i] + b.bytes[i] + carry;
        if (sum > BYTE_T_MAX)
        {
            // max value we can put into this byte
            a->bytes[i] = sum % BYTE_T_MAX;
            // save to carry
            carry = sum / BYTE_T_MAX;
        }
        else
        {
            a->bytes[i] = sum;
            // flush carry because we have place to put values
            carry = 0;
        }
    }
}

huge_long_t huge_long_t_multiply(const huge_long_t a, const huge_long_t b)
{
    if (a.size != b.size)
    {
        printf("a.size != b.size");
        exit(1);
    }
    // we save multiplication into result var
    huge_long_t result = huge_long_t_make_zero(a.size);
    for (size_t i = 0; i < b.size; i++)
    {
        int carry = 0;
        // inner multiplication (multiply one "b" byte on all "a" bytes )
        for (size_t j = 0; j < a.size; j++)
        {
            // sum cannot be bigger than 255 * 255
            int sum = a.bytes[j] * b.bytes[i] + carry;

            if (sum > BYTE_T_MAX)
            {
                // max value we can put into this byte
                result.bytes[j] += sum % BYTE_T_MAX;
                // save to carry
                carry = sum / BYTE_T_MAX;
            }
            else
            {
                result.bytes[j] += sum;
                // flush carry because we have place to put values
                carry = 0;
            }
        }
    }
    return result;
}

/*
get last valid byte for @num
@num is number that is from bytes
*/
int getLastByte(const byte_t *const num, const size_t size)
{
    for (int i = size; i >= 0; --i)
    {
        if (num[i] != 0)
        {
            return i;
        }
    }
    return 0;
}

void printByte(byte_t b)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((b << i) & 0x80));
    }
}

void printBytes(const byte_t *const num, const size_t size, char sep = '\t')
{
    for (size_t i = 0; i < size; i++)
    {
        printByte(num[i]);
        if (sep != '\0')
            printf("%c", sep);
    }
    printf("\n");
}

void printBytesReverse(const byte_t *const num, const size_t size, char sep = '\t')
{
    for (size_t i = 0; i < size; ++i)
    {
        printByte(num[(size - 1) - i]);
        if (sep != '\0')
            printf("%c", sep);
    }
    printf("\n");
}

int main()
{
    huge_long_t num = huge_long_t_from_int(123321);
    huge_long_t num2 = huge_long_t_from_int(123321);

    huge_long_t_add_assign(&num, num2);

    printf("%d\n", huge_long_t_is_zero(num));
    printf("after addition num: \n");
    printBytesReverse(num.bytes, num.size, ' ');
    printf("num2: \n");
    printBytesReverse(num2.bytes, num2.size, ' ');
    // flush
    huge_long_t_delete(&num);
    huge_long_t_delete(&num2);

    num = huge_long_t_from_int(321);
    num2 = huge_long_t_from_int(123);

    huge_long_t result = huge_long_t_multiply(num, num2);

    printf("multiply result: \n");
    printBytesReverse(result.bytes, result.size, ' ');
    printf("num: \n");
    printBytesReverse(num.bytes, num.size, ' ');
    printf("num2: \n");
    printBytesReverse(num2.bytes, num2.size, ' ');

    huge_long_t_delete(&num);
    huge_long_t_delete(&num2);
    return 0;
}