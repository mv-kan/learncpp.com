#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/*
100100

module by 2^8 (one byte) and you get decimal for first byte

devide by 2^8 (one byte) and you get decimal for second byte

*/
// HUGE
#define BYTE_T_MAX 256
#define DEBUG 0
// additional info durring execution
#define DEBUG_EXT_ADDITION 0
#define DEBUG_EXT_MULTIPLY 0
#define DEBUG_EXT_PARSE 0
// if DEBUG set HUGE_SIZE to sizeof(int)
// because multiplying is depends on this value
// why? it is complicated, better take a look at huge_t_multiply function
#define HUGE_SIZE 600

typedef unsigned char byte_t;

void printByte(byte_t b)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d", !!((b << i) & 0x80));
    }
}
void printBytes(const byte_t *const num, const size_t size, const char sep = ' ')
{
    for (size_t i = 0; i < size; i++)
    {
        printByte(num[i]);
        if (sep != '\0')
            printf("%c", sep);
    }
    printf("\n");
}
void printBytesReverse(const byte_t *const num, const size_t size, const char sep = ' ')
{
    for (size_t i = 0; i < size; i++)
    {
        printByte(num[size - 1 - i]);
        if (sep != '\0')
            printf("%c", sep);
    }
    printf("\n");
}

// least significant endian
struct huge_t
{
    // capacity
    size_t size = 0;
    byte_t *bytes = nullptr;
};

huge_t huge_t_make_zero(const size_t size)
{
    // static int i = 0;
    // printf("huge_t_make_zero: %d\n", ++i);
    huge_t num;
    num.bytes = (byte_t *)malloc(size * sizeof(byte_t));
    num.size = size;
    memset(num.bytes, 0, size);
    return num;
}

// @initvalue init value in range of size_t
// @size number of bytes in huge_t
huge_t huge_t_init(size_t init_value, const size_t size)
{
    huge_t num = huge_t_make_zero(size);
    int ibytes = 0;
    while (init_value > 0)
    {
        // we put the value to byte
        num.bytes[ibytes] = init_value % BYTE_T_MAX;
        // increment iBytenum to set it to empty byte in @bytenum
        ibytes++;
        // devide result
        init_value /= BYTE_T_MAX;
    }
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

void huge_t_print(const huge_t num, char sep = ' ')
{
    for (size_t i = 0; i < num.size; ++i)
    {
        printByte(num.bytes[(num.size - 1) - i]);
        if (sep != '\0')
            printf("%c", sep);
    }
    printf("\n");
}

void huge_t_set(huge_t *num, size_t value)
{
    int ibytes = 0;
    memset(num->bytes, 0, num->size);
    while (value > 0)
    {
        // we put the value to byte
        num->bytes[ibytes] = value % BYTE_T_MAX;
        // increment iBytenum to set it to empty byte in @bytenum
        ibytes++;
        // devide result
        value /= BYTE_T_MAX;
    }
}

void huge_t_delete(huge_t *const num)
{
    if (num->bytes)
    {
        // static int i = 0;
        // printf("huge_t_delete: %d\n", ++i);
        free(num->bytes);
        // do not uncomment this, some code expects after delete var size being where is was
        // num->bytes = nullptr;
        // num->size = 0;
    }
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

void huge_t_copy(huge_t *const ptr, const huge_t num)
{
    if (ptr->size < num.size)
    {
        printf("huge_t_copy: ptr->size < num.size\n");
        exit(1);
    }
    memset(ptr->bytes, 0, ptr->size);
    for (size_t i = 0; i < num.size; i++)
    {
        ptr->bytes[i] = num.bytes[i];
    }
}

#define CACHE_SIZE 2000
huge_t cache[CACHE_SIZE];

// push ptr into cache
// returns false if not success
bool huge_t_cache_push(huge_t *const ptr)
{
    if (ptr)
    {
        for (size_t i = 0; i < CACHE_SIZE; i++)
        {
            if (cache[i].size == 0 && cache[i].bytes == NULL)
            {
                memset(ptr->bytes, 0, ptr->size);
                cache[i].bytes = ptr->bytes;
                cache[i].size = ptr->size;
                return true;
            }
        }
        return false;
    }
    else
    {
        printf("huge_t_cache_push: there shouldn't be huge_t NULL poiners, this is error");
        exit(1);
    }
}

/*
get from cache already created huge_t with size of @size
huge_t will be deleted from cache
@ptr var where to put huge_t from cache
nullptr in bytes and 0 in size considered as empty in huge_t cache
@returns true if cache hit, false if cache miss
*/
bool huge_t_cache_get(huge_t *const ptr, const size_t size)
{
    if (ptr)
    {
        for (size_t i = 0; i < CACHE_SIZE; i++)
        {
            if (cache[i].size == size)
            {
                memset(cache[i].bytes, 0, cache[i].size);
                ptr->bytes = cache[i].bytes;
                ptr->size = cache[i].size;
                cache[i].size = 0;
                cache[i].bytes = NULL;
                // cache hit
                return true;
            }
        }
        // cache miss
        return false;
    }
    else
    {
        printf("huge_t_cache_get: there shouldn't be huge_t NULL poiners, this is error");
        exit(1);
    }
}

// quick delete and quick init are tied together
void huge_t_quick_delete(huge_t *const ptr)
{
    if (!huge_t_cache_push(ptr))
    {
        huge_t_delete(ptr);
        ptr->bytes = NULL;
        ptr->size = 0;
        return;
        printf("huge_t_quick_delete: cache is full");
        exit(1);
    }
    else
    {
        ptr->bytes = NULL;
        ptr->size = 0;
    }
}
// quick init is universal function that makes check,
// creates new, or get from cache unused huge_t
void huge_t_quick_init(huge_t *const ptr, const size_t size)
{
    if (ptr)
    {
        if (ptr->size == size)
        {
            memset(ptr->bytes, 0, size);
            return;
        }
        else
        {
            huge_t_quick_delete(ptr);
            // if not cache hit
            if (!huge_t_cache_get(ptr, size))
            {
                *ptr = huge_t_make_zero(size);
                return;
            }
        }
    }
    else
    {
        printf("huge_t_quick_init: no dynamic huge_t, it will destroy readability of this code!");
        exit(1);
    }
}

void huge_t_add(huge_t *const ptr, const huge_t a, const huge_t b)
{
    if (!ptr)
    {
        printf("huge_t_add: ptr == nullptr");
        exit(1);
    }
    else
    {
        if (ptr->size < a.size)
        {
            huge_t_quick_init(ptr, a.size);
        }
        else
        {
            memset(ptr->bytes, 0, ptr->size);
        }
    }
#if DEBUG_EXT_ADDITION
    printf("a, b: \n");
    huge_t_print(a);
    huge_t_print(b);
#endif

    int carry = 0;
    for (size_t i = 0; i < a.size && i < b.size; i++)
    {
        // sum cannot be bigger than 255 + 255
        int sum = a.bytes[i] + b.bytes[i] + carry;
#if DEBUG_EXT_ADDITION
        printf("a.bytes[%zu] = %d, b.bytes[%zu] = %d\n", i, a.bytes[i], i, b.bytes[i]);
#endif
        if (sum >= BYTE_T_MAX)
        {
            // max value we can put into this byte
            ptr->bytes[i] = sum % BYTE_T_MAX;
            // save to carry
            carry = sum / BYTE_T_MAX;
        }
        else
        {
            ptr->bytes[i] = sum;
            // flush carry because we have place to put values
            carry = 0;
        }
    }
    // edge case for ptr more than a and b and sum of a and b leads to overflow
    if (carry > 0 && (ptr->size > a.size || ptr->size > b.size))
    {

        size_t least_size = a.size > b.size ? b.size : a.size;

        // ptr's value is set to zero, so we can just assign carry to it
        ptr->bytes[least_size] = carry;
    }
}

void huge_t_add_assign(huge_t *const a, const huge_t b)
{
    // // huge_t_multiply require ability to add different size huge_t
    // if (a->size != b.size)
    // {
    //     printf("huge_t_add_assign: a.size != b.size");
    //     exit(1);
    // }
    // we save multiplication into result var
    huge_t result;
    huge_t_quick_init(&result, a->size);
    huge_t_add(&result, *a, b);
    huge_t_quick_delete(a);
    a->bytes = result.bytes;
    a->size = result.size;
}

huge_t huge_t_get_second_complement(const huge_t a)
{
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

void huge_t_convert_second_complement(huge_t *const a)
{
    // to get second complement we need to add one
    huge_t one = huge_t_make_zero(a->size);
    one.bytes[0] = 1;

    for (size_t i = 0; i < a->size; i++)
    {
        a->bytes[i] = ~a->bytes[i];
    }
    huge_t_add_assign(a, one);
    huge_t_delete(&one);
}

void huge_t_subtract_assign(huge_t *const a, const huge_t b)
{
    if (a->size != b.size)
    {
        printf("huge_t_subtract_assign: a.size != b.size\n");
        exit(1);
    }
    huge_t complement = huge_t_get_second_complement(b);
    // #if DEBUG_EXT
    // printf("complement of b: \n");
    // huge_t_print(complement);
    // #endif
    huge_t_add_assign(a, complement);
    huge_t_delete(&complement);
}

void huge_t_multiply_slow(huge_t *const ptr, const huge_t a, const huge_t b)
{
    // This is messed up, the moment it worked I forgot implementation
    // so please don't touch it, because nobody knows how it works
    if (a.size != b.size)
    {
        printf("huge_t_multiply_slow: a.size != b.size");
        exit(1);
    }
    // if nullptr
    if (ptr)
    {
        // not good size
        if (ptr->size != a.size)
        {
            huge_t_delete(ptr);

            *ptr = huge_t_make_zero(a.size);
        }
        else
        {
            memset(ptr->bytes, 0, ptr->size);
        }
    }
    else
    {
        huge_t_delete(ptr);

        *ptr = huge_t_make_zero(a.size);
    }

    // this is O(n^2) but I do care
    // distributive property used here
    for (size_t i = 0; i < b.size; i++)
    {
        int carry = 0;
        // inner multiplication (multiply one "b" byte on all "a" bytes )
        for (size_t j = 0; j < a.size; j++)
        {
            // sum cannot be bigger than 255 * 255
            int sum = a.bytes[j] * b.bytes[i] + carry;
            // @result_index is index of results bytes
            //
            int result_index = j + i;
            if (sum >= BYTE_T_MAX)
            {
                // max value we can put into this byte

                // if existing result.bytes[i] + sum is bigger than BYTE_T_MAX we get overflow and wrong answer
                // to fix this we just add to @carry (result.bytes[i] + sum) / BYTE_T_MAX
                // with this addition if there is overflow something will be added
                // if no overflow then the expression is zero
                // PS carry has to be calculated before result because we change result

                // pre result is calculated result in case of overflow of char
                int pre_result = (ptr->bytes[result_index] + (sum % BYTE_T_MAX));
                carry = sum / BYTE_T_MAX + (pre_result / BYTE_T_MAX);

                ptr->bytes[result_index] = pre_result;
            }
            else
            {
                // flush carry because we have place to put values
                // for explanation look for comment in if statement

                // pre result is calculated result in case of overflow of char
                int pre_result = (ptr->bytes[result_index] + (sum % BYTE_T_MAX));
                carry = pre_result / BYTE_T_MAX;

                ptr->bytes[result_index] = pre_result;
            }
        }
    }
}

// actually it is byte shift right, because huge_t is little endian
// ps byte shift to right is like multiplying num on 2^8
void huge_t_byte_shift_left(huge_t *const ptr)
{
    byte_t prev = ptr->bytes[0];
    ptr->bytes[0] = 0;
    for (size_t i = 1; i < ptr->size; i++)
    {
        byte_t tmp;
        tmp = ptr->bytes[i];
        ptr->bytes[i] = prev;
        prev = tmp;
    }
}

// divide on 2^8
void huge_t_byte_shift_right(huge_t *const ptr)
{
    ptr->bytes[ptr->size - 1] = 0;
    for (size_t i = 0; i < ptr->size - 1; i++)
    {
        ptr->bytes[i] = ptr->bytes[i + 1];
    }
}

size_t huge_t_get_last_byte_index(huge_t a)
{
    for (size_t i = 0; i < a.size; ++i)
    {
        if (a.bytes[(a.size - 1) - i] != 0)
            return (a.size - 1) - i;
    }
    return 0;
}

// create new huge_t and assign it to ptr if ptr is null or ptr->size != value.size
// if ptr->size == value.size then just flush ptr
// think and delete this atrocity
void huge_t_ptr_to_size(huge_t *ptr, const huge_t value)
{
    if (ptr)
    {
        if (ptr->size != value.size)
        {
            printf("huge_t_ptr_to_size: ptr->size != value.size\n");
            exit(1);
        }

        memset(ptr->bytes, 0, ptr->size);
    }
}

// do not save numerical digit
void huge_t_split_at(huge_t *const ptr, huge_t *const ptr2, const huge_t value, size_t at)
{
    // allocate at + 1 bytes for ptr, when you would want to optimize it
    huge_t_quick_init(ptr, at + 1);
    huge_t_quick_init(ptr2, at + 1);

    // low
    for (size_t i = 0; i < at; i++)
    {
        ptr->bytes[i] = value.bytes[i];
    }
    // high
    // at * 2 + 1 is the result of get_last_byte_index
    // we computated at in multiply func and we reverse computate last byte index
    // and we add + 1 because it is last index
    for (size_t i = at; i < at * 2 + 1 + 1; i++)
    {
        ptr2->bytes[i - at] = value.bytes[i];
    }
}

// karatsuba algorithm
void huge_t_multiply(huge_t *const ptr, const huge_t a, const huge_t b)
{
    // https://en.wikipedia.org/wiki/Karatsuba_algorithm#Example
    // static int counter = 0;
    // printf("huge_t_multiply call: %d\n", ++counter);
#if DEBUG_EXT_MULTIPLY
    static int i = 0;
    int funcid = i;
    i++;
    printf("fid = %d a, b: \n", funcid);
    huge_t_print(a);
    huge_t_print(b);
#endif
    // check ptr for not null
    if (ptr)
    {
        if (ptr->size < a.size)
        {
            huge_t_quick_init(ptr, a.size);
        }
        else
        {
            memset(ptr->bytes, 0, ptr->size);
        }
    }
    else
    {
        printf("huge_t_multiply: no null ptr in huge_t pointer!!!");
        exit(1);
    }

    // if zero then just set 0
    if (huge_t_is_zero(a) || huge_t_is_zero(b))
    {
        huge_t_set(ptr, 0);

#if DEBUG_EXT_MULTIPLY
        printf("fid = %d ptr: \n", funcid);
        huge_t_print(*ptr);
#endif
        return;
    }
    size_t last_byte_a = huge_t_get_last_byte_index(a);
    size_t last_byte_b = huge_t_get_last_byte_index(b);
    // little multiplication, we can do just char * char
    if (last_byte_a == 0 && last_byte_b == 0)
    {
        huge_t_set(ptr, a.bytes[0] * b.bytes[0]);

#if DEBUG_EXT_MULTIPLY
        printf("fid = %d ptr: \n", funcid);
        huge_t_print(*ptr);
#endif
        return;
    }
    // if one return thing that is not one
    if (last_byte_a == 0 && a.bytes[0] == 1)
    {
        huge_t_copy(ptr, b);

#if DEBUG_EXT_MULTIPLY
        printf("fid = %d ptr: \n", funcid);
        huge_t_print(*ptr);
#endif
        return;
    }
    else if (last_byte_b == 0 && b.bytes[0] == 1)
    {
        huge_t_copy(ptr, a);

#if DEBUG_EXT_MULTIPLY
        printf("fid = %d ptr: \n", funcid);
        huge_t_print(*ptr);
#endif
        return;
    }

    // calc center of a or b
    size_t m = last_byte_a > last_byte_b ? (last_byte_a + 1) / 2 : (last_byte_b + 1) / 2;

    // Split the digit sequences in the middle.
    huge_t high1, low1, high2, low2;

    huge_t_split_at(&low1, &high1, a, m);
    huge_t_split_at(&low2, &high2, b, m);
    // divide highs on 2^8 because split_at saves numerical digit
    // huge_t_byte_shift_right(&high1);
    // huge_t_byte_shift_right(&high2);
#if DEBUG_EXT_MULTIPLY

    printf("fid = %d high1, low1: \n", funcid);
    huge_t_print(high1);
    huge_t_print(low1);

    printf("fid = %d high2, low2: \n", funcid);
    huge_t_print(high2);
    huge_t_print(low2);

#endif
    // each huge_t_multiply function has to have its own dedicated memory for these variables
    huge_t z0, z1, z2;
    huge_t_quick_init(&z0, a.size);
    huge_t_quick_init(&z1, a.size);
    huge_t_quick_init(&z2, a.size);

    // find z0
    huge_t_multiply(&z0, low1, low2);

    huge_t sum1;
    huge_t sum2;
    huge_t_quick_init(&sum1, a.size);
    huge_t_quick_init(&sum2, a.size);

    // find z1
    huge_t_add(&sum1, low1, high1);
    huge_t_add(&sum2, low2, high2);
#if DEBUG_EXT_MULTIPLY
    printf("fid = %d sum1: \n", funcid);
    huge_t_print(sum1);

    printf("fid = %d sum2: \n", funcid);
    huge_t_print(sum2);
#endif

    huge_t_multiply(&z1, sum1, sum2);
    // find z2
    huge_t_multiply(&z2, high1, high2);

#if DEBUG_EXT_MULTIPLY
    printf("fid = %d z0: \n", funcid);
    huge_t_print(z0);

    printf("fid = %d z1: \n", funcid);
    huge_t_print(z1);

    printf("fid = %d z2: \n", funcid);
    huge_t_print(z2);
#endif

    // (z1 - z2 - z0) * 2^8
    huge_t_subtract_assign(&z1, z2);
#if DEBUG_EXT_MULTIPLY
    printf("fid = %d z1 - z2: \n", funcid);
    huge_t_print(z1);
#endif
    huge_t_subtract_assign(&z1, z0);
#if DEBUG_EXT_MULTIPLY
    printf("fid = %d z1 - z0: \n", funcid);
    huge_t_print(z1);
#endif
    // unoptimized I can rewrite byte shift so we can shift multiple bytes, but I will do it later
    // power of z1 and z2 depends on where we split the numbers
    // that's why we use m here
    for (size_t i = 0; i < m; i++)
    {
        huge_t_byte_shift_left(&z1);
    }
#if DEBUG_EXT_MULTIPLY
    printf("fid = %d z1 << 1 byte: \n", funcid);
    huge_t_print(z1);
#endif
    // z2 * 2^16, that's why I make shift two times
    // make sure that it is calculated BEFORE z1 calculated
    for (size_t i = 0; i < m; i++)
    {
        huge_t_byte_shift_left(&z2);
        huge_t_byte_shift_left(&z2);
    }

    // calculate result
    huge_t_add_assign(ptr, z2);
    huge_t_add_assign(ptr, z1);
    huge_t_add_assign(ptr, z0);
#if DEBUG_EXT_MULTIPLY
    printf("fid = %d new z0: \n", funcid);
    huge_t_print(z0);

    printf("fid = %d new z1: \n", funcid);
    huge_t_print(z1);

    printf("fid = %d new z2: \n", funcid);
    huge_t_print(z2);

    printf("fid = %d ptr: \n", funcid);
    huge_t_print(*ptr);

#endif
    // delete it
    huge_t_quick_delete(&z0);
    huge_t_quick_delete(&z1);
    huge_t_quick_delete(&z2);
    huge_t_quick_delete(&sum1);
    huge_t_quick_delete(&sum2);
    huge_t_quick_delete(&high1);
    huge_t_quick_delete(&high2);
    huge_t_quick_delete(&low1);
    huge_t_quick_delete(&low2);
}

void huge_t_multiply_assign(huge_t *const a, const huge_t b)
{
    // This is messed up, the moment it worked I forgot implementation
    // so please don't touch it, because nobody knows how it works
    if (a->size != b.size)
    {
        printf("huge_t_multiply_assign: a.size != b.size");
        exit(1);
    }
    // we save multiplication into result var
    huge_t result = huge_t_make_zero(a->size);
    huge_t_multiply(&result, *a, b);
    huge_t_delete(a);
    a->bytes = result.bytes;
}

void huge_t_subtract(huge_t *const ptr, const huge_t a, const huge_t b)
{
    if (a.size != b.size)
    {
        printf("a.size != b.size");
        exit(1);
    }
    huge_t complement = huge_t_get_second_complement(b);
    huge_t_add(ptr, a, complement);
    huge_t_delete(&complement);
}

void huge_t_divide(huge_t *const ptr, const huge_t a, const huge_t b)
{
    if (a.size != b.size)
    {
        printf("huge_t_divide: a.size != b.size");
        exit(1);
    }
    // if nullptr
    if (ptr)
    {
        // not good size
        if (ptr->size != a.size)
        {
            huge_t_delete(ptr);

            *ptr = huge_t_make_zero(a.size);
        }
        else
        {
            memset(ptr->bytes, 0, ptr->size);
        }
    }
    else
    {
        huge_t_delete(ptr);

        *ptr = huge_t_make_zero(a.size);
    }
}

// huge_t huge_t_divide(const huge_t a, const huge_t b) {

// }

// huge_t huge_t_remainder(const huge_t a, const huge_t b) {

// }
#include <time.h>
#define TEST_VALUES_SIZE 100
// returns array with size * 3 size
// from 0 to size there are first operands (a)
// from size to size * 2 there are second operands (b)
// from size * 2 to size * 3 there are result
// @oper is action, like + - / or *
int *test_generate_values(const size_t size, const char oper)
{
    size_t end_a = size;
    size_t end_b = (size * 2);
    size_t end_result = (size * 3);

    // malloc size * 3 * sizeof(int) array
    int *values = (int *)malloc(size * 3 * sizeof(int));
    // fill from 0 to size * 2 with random values
    for (size_t i = 0; i < end_b; i++)
    {
        values[i] = rand() % 30000;
    }

    // I dont know what is lambda sorry
    // fill from size * 2 to size * 3 with results
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a in this loop
        size_t i_a = i - end_b;
        size_t i_b = i - end_a;
        switch (oper)
        {
        case '+':
            values[i] = values[i_a] + values[i_b];
            break;
        case '-':
            values[i] = values[i_a] - values[i_b];
            break;
        case '*':
            values[i] = values[i_a] * values[i_b];
            break;
        case '/':
            values[i] = values[i_a] / values[i_b];
            break;
        default:
            printf("test_generate_values: no such oper as %c", oper);
            exit(1);
            break;
        }
    }

    // return result

    return values;
}

void test_huge_t_add()
{
    /* addition */
    size_t values_size = TEST_VALUES_SIZE;
    size_t end_a = TEST_VALUES_SIZE;
    size_t end_b = TEST_VALUES_SIZE * 2;
    size_t end_result = TEST_VALUES_SIZE * 3;

    int *test_values = test_generate_values(values_size, '+');
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a
        size_t i_a = i - end_b;
        // index of b
        size_t i_b = i - end_a;

        int c = test_values[i];
        int a = test_values[i_a];
        int b = test_values[i_b];

        huge_t num = huge_t_from_int(a);
        huge_t num2 = huge_t_from_int(b);
        huge_t result;
        huge_t_add(&result, num, num2);
        huge_t true_result = huge_t_from_int(c);

        if (memcmp(result.bytes, true_result.bytes, sizeof(int)) != 0)
        {
            printf("test_huge_t_add: test no %zu FAILED!!!, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }
        else
        {
            printf("test_huge_t_add: test no %zu OK, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }

        // flush
        huge_t_delete(&num);
        huge_t_delete(&num2);
        huge_t_delete(&result);
        huge_t_delete(&true_result);
    }
    free(test_values);
}

void test_huge_t_multiply()
{
    size_t values_size = TEST_VALUES_SIZE;
    size_t end_a = TEST_VALUES_SIZE;
    size_t end_b = TEST_VALUES_SIZE * 2;
    size_t end_result = TEST_VALUES_SIZE * 3;

    int *test_values = test_generate_values(values_size, '*');
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a
        size_t i_a = i - end_b;
        // index of b
        size_t i_b = i - end_a;

        int c = test_values[i];
        int a = test_values[i_a];
        int b = test_values[i_b];

        huge_t num = huge_t_from_int(a);
        huge_t num2 = huge_t_from_int(b);
        huge_t result = huge_t_from_int(0);
        huge_t_multiply(&result, num, num2);
        huge_t true_result = huge_t_from_int(c);

        if (memcmp(result.bytes, true_result.bytes, sizeof(int)) != 0)
        {
            printf("test_huge_t_multiply: test no %zu FAILED!!!, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
            huge_t_print(result);
            huge_t_print(true_result);
        }
        else
        {
            printf("test_huge_t_multiply: test no %zu OK, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }

        // flush
        huge_t_delete(&num);
        huge_t_delete(&num2);
        huge_t_delete(&result);
        huge_t_delete(&true_result);
    }
    free(test_values);
}

void test_huge_t_subtract()
{
    size_t values_size = TEST_VALUES_SIZE;
    size_t end_a = TEST_VALUES_SIZE;
    size_t end_b = TEST_VALUES_SIZE * 2;
    size_t end_result = TEST_VALUES_SIZE * 3;

    int *test_values = test_generate_values(values_size, '-');
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a
        size_t i_a = i - end_b;
        // index of b
        size_t i_b = i - end_a;

        int c = test_values[i];
        int a = test_values[i_a];
        int b = test_values[i_b];
        if (a - b < 0)
            continue;
        huge_t num = huge_t_from_int(a);
        huge_t num2 = huge_t_from_int(b);
        huge_t result;
        huge_t_subtract(&result, num, num2);
        huge_t true_result = huge_t_from_int(c);

        if (memcmp(result.bytes, true_result.bytes, sizeof(int)) != 0)
        {
            printf("test_huge_t_subtract: test no %zu FAILED!!!, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }
        else
        {
            printf("test_huge_t_subtract: test no %zu OK, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }

        // flush
        huge_t_delete(&num);
        huge_t_delete(&num2);
        huge_t_delete(&result);
        huge_t_delete(&true_result);
    }
    free(test_values);
}

void test_huge_t_add_assign()
{
    /* addition */
    size_t values_size = TEST_VALUES_SIZE;
    size_t end_a = TEST_VALUES_SIZE;
    size_t end_b = TEST_VALUES_SIZE * 2;
    size_t end_result = TEST_VALUES_SIZE * 3;

    int *test_values = test_generate_values(values_size, '+');
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a
        size_t i_a = i - end_b;
        // index of b
        size_t i_b = i - end_a;

        int c = test_values[i];
        int a = test_values[i_a];
        int b = test_values[i_b];

        huge_t num = huge_t_from_int(a);
        huge_t num2 = huge_t_from_int(b);
        huge_t true_result = huge_t_from_int(c);
        huge_t_add_assign(&num, num2);

        if (memcmp(num.bytes, true_result.bytes, sizeof(int)) != 0)
        {
            printf("test_huge_t_add_assign: test no %zu FAILED!!!, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }
        else
        {
            printf("test_huge_t_add_assign: test no %zu OK, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }

        // flush
        huge_t_delete(&num);
        huge_t_delete(&num2);
        huge_t_delete(&true_result);
    }
    free(test_values);
}

void test_huge_t_multiply_assign()
{
    size_t values_size = TEST_VALUES_SIZE;
    size_t end_a = TEST_VALUES_SIZE;
    size_t end_b = TEST_VALUES_SIZE * 2;
    size_t end_result = TEST_VALUES_SIZE * 3;

    int *test_values = test_generate_values(values_size, '*');
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a
        size_t i_a = i - end_b;
        // index of b
        size_t i_b = i - end_a;

        int c = test_values[i];
        int a = test_values[i_a];
        int b = test_values[i_b];

        huge_t num = huge_t_from_int(a);
        huge_t num2 = huge_t_from_int(b);
        huge_t true_result = huge_t_from_int(c);
        huge_t_multiply_assign(&num, num2);

        if (memcmp(num.bytes, true_result.bytes, sizeof(int)) != 0)
        {
            printf("test_huge_t_multiply_assign: test no %zu FAILED!!!, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
            huge_t_print(num);
            huge_t_print(true_result);
        }
        else
        {
            printf("test_huge_t_multiply_assign: test no %zu OK, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }

        // flush
        huge_t_delete(&num);
        huge_t_delete(&num2);
        huge_t_delete(&true_result);
    }
    free(test_values);
}

void test_huge_t_subtract_assign()
{
    size_t values_size = TEST_VALUES_SIZE;
    size_t end_a = TEST_VALUES_SIZE;
    size_t end_b = TEST_VALUES_SIZE * 2;
    size_t end_result = TEST_VALUES_SIZE * 3;

    int *test_values = test_generate_values(values_size, '-');
    for (size_t i = end_b; i < end_result; i++)
    {
        // index of a
        size_t i_a = i - end_b;
        // index of b
        size_t i_b = i - end_a;

        int c = test_values[i];
        int a = test_values[i_a];
        int b = test_values[i_b];

        if (a - b < 0)
            continue;
        huge_t num = huge_t_from_int(a);
        huge_t num2 = huge_t_from_int(b);
        huge_t true_result = huge_t_from_int(c);
        huge_t_subtract_assign(&num, num2);

        if (memcmp(num.bytes, true_result.bytes, sizeof(int)) != 0)
        {
            printf("test_huge_t_subtract_assign: test no %zu FAILED!!!, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }
        else
        {
            printf("test_huge_t_subtract_assign: test no %zu OK, a=%d, b=%d, true_result=%d\n", i_a, a, b, c);
        }

        // flush
        huge_t_delete(&num);
        huge_t_delete(&num2);
        huge_t_delete(&true_result);
    }
    free(test_values);
}

void test_huge_t_byte_shift_left()
{
    huge_t num = huge_t_from_int(238);
    huge_t true_result = huge_t_from_int(60928); // 60928 is 238 * 256
    huge_t_byte_shift_left(&num);

    if (memcmp(num.bytes, true_result.bytes, sizeof(int)) != 0)
    {
        printf("test_huge_t_byte_shift_left: FAILED!!!\n");
    }
    else
    {
        printf("test_huge_t_byte_shift_left: OK\n");
    }

    // flush
    huge_t_delete(&num);
    huge_t_delete(&true_result);
}

void test_huge_t_get_last_byte_index()
{
    huge_t num = huge_t_from_int(300);
    size_t true_result = 1;
    size_t last_byte = huge_t_get_last_byte_index(num);

    if (last_byte != true_result)
    {
        printf("test_huge_t_byte_shift_left: FAILED!!!\n");
    }
    else
    {
        printf("test_huge_t_byte_shift_left: OK\n");
    }

    // flush
    huge_t_delete(&num);
}
// END HUGE
// start input code

#define MAX_CHAR_INPUT 1000
char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// converts char digit to decimal number
int digitToDecimal(char digit)
{
    char *findChar;
    int index;

    for (char *i = digits; *i != '\0'; i++)
    {
        if (*i == digit)
        {
            findChar = i;
            break;
        }
    }

    index = (int)(findChar - digits);

    return index;
}

// converts decimal num to digit
// must be less than 36 or more or equal 0
char decimalToDigit(int dec)
{
    if (dec < 0 || dec > 36)
        return '?';
    return digits[dec];
}

// char *to_str(huge_t num, int num_system)
// {
// }

huge_t parse_str(char *str, int num_system)
{
    int len = 0;
    // calc len without strlen
    for (char *i = str; *i != '\0'; i++)
    {
        len++;
    }

    huge_t result = huge_t_make_zero(HUGE_SIZE);
    huge_t num_digit = huge_t_init(1, HUGE_SIZE); // numerical digit
    huge_t digit_to_dec = huge_t_make_zero(HUGE_SIZE);
    huge_t num_sys = huge_t_init((size_t)num_system, HUGE_SIZE);
    // tmp variable, less malloc and free operations
    huge_t tmp = huge_t_make_zero(HUGE_SIZE);

    for (int i = len - 1; i >= 0; --i)
    {
        // convert num in numericalSystem to decimal
        char digit = str[i];
        // here I am just being lazy
        huge_t_set(&digit_to_dec, (size_t)digitToDecimal(digit));

        // multiply numerical digit on numerical system to get value in decimal
        huge_t_multiply(&tmp, num_digit, digit_to_dec);

        huge_t_add_assign(&result, tmp);

        huge_t_multiply_assign(&num_digit, num_sys);
#if DEBUG_EXT_PARSE
        printf("iter%d tmp:\n", i);
        huge_t_print(tmp);
        printf("iter%d result:\n", i);
        huge_t_print(result);
        printf("iter%d num_digit:\n", i);
        huge_t_print(num_digit);
        printf("iter%d digit_to_dec:\n", i);
        huge_t_print(digit_to_dec);
        printf("iter%d num_sys:\n", i);
        huge_t_print(num_sys);
#endif
    }
    huge_t_delete(&num_digit);
    huge_t_delete(&digit_to_dec);
    huge_t_delete(&num_sys);
    huge_t_delete(&tmp);
    return result;
}

int main()
{
#if !DEBUG
    int m = 0;
    int k = 0;
    char A[MAX_CHAR_INPUT + 1];

    scanf("%d %d", &m, &k);
    scanf("%s", A);

    huge_t num = parse_str(A, m);
    // char *str = to_str(num, k);

    // printf("%s", str);
    // converting numbers

    // huge_t_print(num);
    printBytesReverse(num.bytes, huge_t_get_last_byte_index(num) + 1);
    huge_t_delete(&num);

#endif // MACRO

#if DEBUG
    srand(0);
    test_huge_t_get_last_byte_index();
    printf("\n");
    test_huge_t_byte_shift_left();
    printf("\n");
    test_huge_t_add();
    printf("\n");
    test_huge_t_subtract();
    printf("\n");
    test_huge_t_multiply();
    printf("\n");

    test_huge_t_add_assign();
    printf("\n");
    test_huge_t_multiply_assign();
    printf("\n");
    test_huge_t_subtract_assign();
    printf("\n");

#endif
    return 0;
}