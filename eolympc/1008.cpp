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
#define MAX_CHARS_INPUT 1000
#define BYTE_SIZE 2000 // this is huge long t size
#define HUGE_T_SIZE BYTE_SIZE
#define BYTE_MAX 256
#define BYTE_T_MAX 256
#define BYTE_T_MAX_VALUE 255
#define DEBUG 1

namespace huge {
    
}


typedef unsigned char byte_t;

void printByte(byte_t b)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((b << i) & 0x80));
    }
}

// least significant endian
struct huge_t
{
    size_t size;
    byte_t *bytes;
};

huge_t huge_t_make_zero(const size_t size)
{
    huge_t num;
    num.bytes = (byte_t *)malloc(size * sizeof(byte_t));
    num.size = size;
    memset(num.bytes, 0, size);
    return num;
}

huge_t huge_t_from_int(int integer) // int not const because we use this variable for calculation
{
    huge_t num = huge_t_make_zero(sizeof(int));
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

void huge_t_delete(const huge_t *const num)
{
    if (num->bytes)
        free(num->bytes);
}

bool huge_t_is_zero(const huge_t num)
{
    for (size_t i = 0; i < num.size; i++)
    {
        if (num.bytes[i] != 0)
            return false;
    }
    return true;
}

huge_t huge_t_copy(const huge_t num)
{
    huge_t num_copy = huge_t_make_zero(num.size);
    for (size_t i = 0; i < num.size; i++)
    {
        num_copy.bytes[i] = num.bytes[i];
    }
    return num_copy;
}

void huge_t_add_assign(huge_t *const a, const huge_t b)
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
        if (sum >= BYTE_T_MAX)
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

huge_t huge_t_add(const huge_t a, const huge_t b) {
    if (a.size != b.size)
    {
        printf("a.size != b.size");
        exit(1);
    }
    huge_t result = huge_t_make_zero(a.size);
    int carry = 0;
    for (size_t i = 0; i < a.size; i++)
    {
        // sum cannot be bigger than 255 + 255
        int sum = a.bytes[i] + b.bytes[i] + carry;
        if (sum >= BYTE_T_MAX)
        {
            // max value we can put into this byte
            result.bytes[i] = sum % BYTE_T_MAX;
            // save to carry
            carry = sum / BYTE_T_MAX;
        }
        else
        {
            result.bytes[i] = sum;
            // flush carry because we have place to put values
            carry = 0;
        }
    }
    return result;
}

huge_t huge_t_multiply(const huge_t a, const huge_t b)
{
    // This is messed up, the moment it worked I forgot implementation
    // so please don't touch it, because nobody knows how it works
    if (a.size != b.size)
    {
        printf("a.size != b.size");
        exit(1);
    }
    // we save multiplication into result var
    huge_t result = huge_t_make_zero(a.size);
    
    // this is O(n^2) but I don't care 
    // distributive property used here
    for (size_t i = 0; i < b.size; i++)
    {
        int carry = 0;
        // inner multiplication (multiply one "b" byte on all "a" bytes )
        for (size_t j = 0; j < a.size; j++)
        {
            // sum cannot be bigger than 255 * 255
            int sum = a.bytes[j] * b.bytes[i] + carry;

            if (sum >= BYTE_T_MAX)
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

huge_t huge_t_get_second_complement(const huge_t a) {
    // to get second complement we need to add one
    huge_t result = huge_t_make_zero(a.size);
    huge_t one = huge_t_make_zero(a.size);
    one.bytes[0] = 1;

    for (size_t i = 0; i < a.size; i++)
    {
        result.bytes[i] = ~a.bytes[i]; 
    }
    huge_t_add_assign(&result, one);
    huge_t_delete(&one);
    return result;
}

void huge_t_print(const huge_t num, char sep=' ') {
    for (size_t i = 0; i < num.size; ++i)
    {
        printByte(num.bytes[(num.size - 1) - i]);
        if (sep != '\0') 
            printf("%c", sep);
    }
    printf("\n");
}

// subtraction by addition
huge_t huge_t_subtract(const huge_t a, const huge_t b) {
    if (a.size != b.size) {
        printf("a.size != b.size");
        exit(1);
    }
    huge_t complement = huge_t_get_second_complement(b);
    return huge_t_add(a, complement);
}

// huge_t huge_t_divide(const huge_t a, const huge_t b) {

// }

// huge_t huge_t_remainder(const huge_t a, const huge_t b) {

// }

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

void test_huge_t_add() {
    /* addition */
    huge_t num = huge_t_from_int(123);
    huge_t num2 = huge_t_from_int(123);
    huge_t result = huge_t_add(num, num2);
    huge_t true_result = huge_t_from_int(246);

    if (memcmp(result.bytes, true_result.bytes, sizeof(int)) != 0) {
        printf("test_huge_t_add: FAILED!!!\n");
    } else {
        printf("test_huge_t_add: OK\n");
    }

    // flush
    huge_t_delete(&num);
    huge_t_delete(&num2);
    huge_t_delete(&result);
    huge_t_delete(&true_result);
}

void test_huge_t_multiply() {
     /* addition */
    huge_t num = huge_t_from_int(123);
    huge_t num2 = huge_t_from_int(123);
    huge_t result = huge_t_multiply(num, num2);
    huge_t true_result = huge_t_from_int(15129);

    if (memcmp(result.bytes, true_result.bytes, sizeof(int)) != 0) {
        printf("test_huge_t_multiply: FAILED!!!\n");
    } else {
        printf("test_huge_t_multiply: OK\n");
    }

    // flush
    huge_t_delete(&num);
    huge_t_delete(&num2);
    huge_t_delete(&result);
    huge_t_delete(&true_result);
}

void test_huge_t_subtraction() {
    /* addition */
    huge_t num = huge_t_from_int(123);
    huge_t num2 = huge_t_from_int(123);
    huge_t result = huge_t_subtract(num, num2);
    huge_t true_result = huge_t_from_int(0);

    if (memcmp(result.bytes, true_result.bytes, sizeof(int)) != 0) {
        printf("test_huge_t_subtraction: FAILED!!!\n");
    } else {
        printf("test_huge_t_subtraction: OK\n");
    }

    // flush
    huge_t_delete(&num);
    huge_t_delete(&num2);
    huge_t_delete(&result);
    huge_t_delete(&true_result);
}

int main()
{
#ifdef DEBUG

    test_huge_t_add();
    test_huge_t_multiply();
    test_huge_t_subtraction();
    
#endif

    /* addition */
    char sep = ' ';
    huge_t num = huge_t_from_int(123);
    huge_t num2 = huge_t_from_int(123);
    huge_t result = huge_t_subtract(num, num2);
    huge_t complement = huge_t_get_second_complement(result);

    printf("num: \n");
    printBytesReverse(num.bytes, num.size, sep);
    printf("num2: \n");
    printBytesReverse(num2.bytes, num2.size, sep);
    printf("result add: \n");
    printBytesReverse(result.bytes, result.size, sep);
    printf("second complement of result: \n");
    huge_t_print(complement);

    // flush
    huge_t_delete(&num);
    huge_t_delete(&num2);
    huge_t_delete(&result);
    huge_t_delete(&complement);

    // num = huge_t_from_int(12332154);
    // num2 = huge_t_from_int(123);
    // result = huge_t_multiply(num, num2);
    // complement = huge_t_get_second_complement(result);
    // /* multiplying */
    // printf("----------------------------\n");
    // printf("num: \n");
    // printBytesReverse(num.bytes, num.size, sep);
    // printf("num2: \n");
    // printBytesReverse(num2.bytes, num2.size, sep);
    // printf("result multiply: \n");  
    // printBytesReverse(result.bytes, result.size, sep);
    // printf("second complement of result: \n");
    // huge_t_print(complement);

    // huge_t_delete(&complement);
    // huge_t_delete(&num);
    // huge_t_delete(&num2);
    // huge_t_delete(&result);

    // /* subtraction */
    // num = huge_t_from_int(2);
    // num2 = huge_t_from_int(1);
    // result = huge_t_subtract(num, num2);
    
    // printf("----------------------------\n");
    // printf("num: \n");
    // printBytesReverse(num.bytes, num.size, sep);
    // printf("num2: \n");
    // printBytesReverse(num2.bytes, num2.size, sep);
    // printf("result subtraction: \n");  
    // printBytesReverse(result.bytes, result.size, sep);

    // huge_t_delete(&num);
    // huge_t_delete(&num2);
    // huge_t_delete(&result);
    // return 0;
}