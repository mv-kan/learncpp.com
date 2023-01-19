#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/*
RULES:
1. there is not huge_t dynamically allocated, they are always stack vars (but not fragments in huge_t)
2. Every huge_t object has capacity of HUGE_T_CAPACITY
*/
// please use just 10-base base
// don't fuck with binary
#define UINT_INTERNAL_BASE 100000000
#define HUGE_T_CAPACITY 1000
#define MAX_CHAR_INPUT 1000
typedef uint64_t uint_internal_t;

struct huge_s
{
    size_t len;
    size_t capacity;
    uint_internal_t *chunks;
};

typedef struct huge_s huge_t;
/*BASIC STUFF START*/
// Basically checks if huge_t ptr as object exists
// if NULL then exit(1), because of RULE 1 no pointers to huge_t object
// if ptr->capacity is not HUGE_T_CAPACITY then exit(1), because this object is not initialized
// proper error handling is not needed for this task
void __huge_t_ptr_check(const huge_t *const ptr)
{
    if (!ptr)
    {
        printf("__huge_t_ptr_check: ptr == NULL\n");
        exit(1);
    }
    else if (ptr->capacity != HUGE_T_CAPACITY)
    {
        printf("__huge_t_ptr_check: huge_t object is not initialized!\n");
        exit(1);
    }
}

// calls everytime when init method is raised
void __huge_t_init(huge_t *const huge)
{
    if (huge)
    {
        size_t size_of_chunks = sizeof(uint_internal_t) * HUGE_T_CAPACITY;
        huge->chunks = (uint_internal_t *)malloc(size_of_chunks);
        memset(huge->chunks, 0, size_of_chunks);
        huge->capacity = HUGE_T_CAPACITY;
        huge->len = 0;
    }
    else
    {
        printf("__huge_t_init: huge == NULL this is unacceptable");
        exit(1);
    }
}
// always call at least this init
// otherwise it is unproper use of huge_t
void huge_t_init_zero(huge_t *const huge, const size_t len)
{
    // __huge_t_init make it automatically zero
    __huge_t_init(huge);
    huge->len = len;
}

void huge_t_init(huge_t *const huge, size_t value, const size_t len)
{
    __huge_t_init(huge);
    huge->len = len;
    for (size_t i = 0; i < len && value > 0; i++)
    {
        huge->chunks[i] = value % UINT_INTERNAL_BASE;

        // devide result
        value /= UINT_INTERNAL_BASE;
    }
}

// when deleted capacity is zero
void __huge_t_delete(huge_t *const huge)
{
    __huge_t_ptr_check(huge);
    if (huge)
    {
        free(huge->chunks);
        huge->capacity = 0;
        huge->len = 0;
        huge->chunks = NULL;
    }
    else
    {
        printf("__huge_t_init: huge == NULL this is unacceptable");
        exit(1);
    }
}

void huge_t_delete(huge_t *const huge)
{
    __huge_t_ptr_check(huge);
    __huge_t_delete(huge);
}

// // to 10-base value if UINT_INTERNAL_BASE is 10-base
// // formating depends on UINT_INTERNAL_BASE
// // if you were to change UINT_INTERNAL_BASE then you have to change this function too
// void huge_t_print(const huge_t huge)
// {
//     __huge_t_ptr_check(&huge);
//     for (size_t i = 0; i < huge.len; i++)
//     {
//         // print from end to start
//         printf("%zu", huge.chunks[huge.len - i - 1] % UINT_INTERNAL_BASE);
//     }
//     if (huge.len == 0)
//     {
//         printf("%d", 0);
//     }
//     printf("\n");
// }

// void huge_t_print_true(const huge_t huge)
// {
//     __huge_t_ptr_check(&huge);
//     for (size_t i = 0; i < huge.len; i++)
//     {
//         // print from end to start
//         printf(" %zu ", huge.chunks[huge.len - i - 1]);
//     }
//     if (huge.len == 0)
//     {
//         printf(" %zu ", (size_t)0);
//     }
//     printf("\n");
// }

void huge_t_set_zero(huge_t *const huge)
{
    __huge_t_ptr_check(huge);
    memset(huge->chunks, 0, huge->capacity * sizeof(uint_internal_t));
}

void huge_t_set(huge_t *const huge, size_t value)
{
    __huge_t_ptr_check(huge);
    huge_t_set_zero(huge);
    // reset to zero
    size_t chunk = 0;
    while (value > 0)
    {
        // we put the value to byte
        huge->chunks[chunk] = value % UINT_INTERNAL_BASE;
        // increment iBytenum to set it to empty byte in @bytenum
        chunk++;
        // devide result
        value /= UINT_INTERNAL_BASE;
    }
    huge->len = chunk;
}

// can fix here, original should be as value not pointer
void huge_t_copy(huge_t *const ptr, huge_t *const original)
{
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(original);
    huge_t_set_zero(ptr);

    ptr->len = original->len;
    for (size_t i = 0; i < ptr->len; i++)
    {
        ptr->chunks[i] = original->chunks[i];
    }
}
/*BASIC STUFF END*/

/*MATH OPERATIONS START*/
bool huge_t_is_zero(const huge_t huge) {
    for (size_t i = 0; i < huge.len; i++)
    {
        if(huge.chunks[i] != 0)
            return false;
    }
    return true;    
}
// overwrites @huge with a + b
void huge_t_add(huge_t *const ptr, const huge_t a, const huge_t b)
{
    // basic checks
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(&a);
    __huge_t_ptr_check(&b);
    huge_t_set_zero(ptr);

    // set the biggest len to huge
    ptr->len = a.len > b.len ? a.len : b.len;

    uint_internal_t carry = 0;
    for (size_t i = 0; i < a.len || i < b.len; i++)
    {
        size_t sum = (size_t)a.chunks[i] + b.chunks[i] + carry;

        if (sum >= UINT_INTERNAL_BASE)
        {
            // max value we can put into this byte
            ptr->chunks[i] = sum % UINT_INTERNAL_BASE;
            // save to carry
            carry = sum / UINT_INTERNAL_BASE;
        }
        else
        {
            ptr->chunks[i] = sum;
            // flush carry because we have place to put values
            carry = 0;
        }
    }
}

void huge_t_add_assign(huge_t *const ptr, const huge_t b)
{
    // basic checks
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(&b);

    huge_t tmp;
    huge_t_init_zero(&tmp, ptr->len);

    huge_t_add(&tmp, *ptr, b);

    huge_t_copy(ptr, &tmp);
    huge_t_delete(&tmp);
}

void huge_t_subtract(huge_t *const ptr, const huge_t a, const huge_t b)
{
    // basic checks
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(&a);
    __huge_t_ptr_check(&b);
    huge_t_set_zero(ptr);
    if (a.len != b.len)
    {
        printf("huge_t_subtract: a.len != b.len\n");
        exit(1);
    }
    ptr->len = a.len;

    uint_internal_t borrow = 0;
    for (size_t i = 0; i < ptr->len; i++)
    {
        // we need to know when subtract is negative
        int64_t subtract = ((int64_t)a.chunks[i] - (int64_t)borrow) - (int64_t)b.chunks[i];
        if (subtract < 0)
        {
            // yes borrow here
            borrow = 1;
            // borrowed things, here we might have conversion error
            // but you just gotta disable it, because here it was explicit type conversion
            uint_internal_t borrowed = ~(uint_internal_t)0 % UINT_INTERNAL_BASE;
            // this is actually subtraction
            borrowed += (uint_internal_t)subtract;
            // assign subtraction of borrowed to result
            ptr->chunks[i] = borrowed;
        }
        else
        {
            // no borrow here
            borrow = 0;

            ptr->chunks[i] = subtract;
        }
    }
}

void huge_t_subtract_assing(huge_t *const ptr, const huge_t b)
{
    // basic checks
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(&b);

    huge_t tmp;
    huge_t_init_zero(&tmp, ptr->len);

    huge_t_subtract(&tmp, *ptr, b);

    huge_t_copy(ptr, &tmp);
    huge_t_delete(&tmp);
}

// make multiplying only for 2 to 36
// this is genious!!!
void huge_t_multiply(huge_t *const ptr, const huge_t a, const uint_internal_t b)
{
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(&a);
    huge_t_set_zero(ptr);

    // set the biggest len to huge
    ptr->len = a.len;

    uint_internal_t carry = 0;
    for (size_t i = 0; i < a.len; i++)
    {
        size_t multiplied = ((size_t)a.chunks[i] * b) + carry;

        if (multiplied >= UINT_INTERNAL_BASE)
        {
            // max value we can put into this byte
            ptr->chunks[i] = multiplied % UINT_INTERNAL_BASE;

            // save to carry
            carry = multiplied / UINT_INTERNAL_BASE;
        }
        else
        {
            ptr->chunks[i] = multiplied;

            // flush carry because we have place to put values
            carry = 0;
        }
    }

    if (carry > 0 && (ptr->len < ptr->capacity))
    {
        ptr->chunks[ptr->len] = carry;
        ptr->len++;
    }
}

void huge_t_multiply_assign(huge_t *const ptr, const uint_internal_t b)
{
    // basic checks
    __huge_t_ptr_check(ptr);

    huge_t tmp;
    huge_t_init_zero(&tmp, ptr->len);

    huge_t_multiply(&tmp, *ptr, b);

    huge_t_copy(ptr, &tmp);
    huge_t_delete(&tmp);
}

// b cannot be bigger than UINT_INTERNAL_BASE otherwise wrong calculation
void huge_t_divide(huge_t *const ptr, const huge_t a, const uint_internal_t b)
{
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(&a);
    huge_t_set_zero(ptr);

    ptr->len = a.len;

    uint_internal_t borrow = 0;
    for (size_t i = 0; i < a.len; i++)
    {
        size_t fromend = a.len - i - 1;
        uint_internal_t sum = borrow + a.chunks[fromend];
        if (sum >= b)
        {
            uint_internal_t division = sum / b;
            uint_internal_t remainder = sum % b;
            ptr->chunks[fromend] = division;
            borrow = remainder * UINT_INTERNAL_BASE;
        }
        else if (sum < b && sum > 0)
        {
            borrow = sum * UINT_INTERNAL_BASE;
        }
    }
}

// b cannot be bigger than UINT_INTERNAL_BASE otherwise wrong calculation
void huge_t_divide_assign(huge_t *const ptr, const uint_internal_t b)
{
    // basic checks
    __huge_t_ptr_check(ptr);

    huge_t tmp;
    huge_t_init_zero(&tmp, ptr->len);

    huge_t_divide(&tmp, *ptr, b);

    huge_t_copy(ptr, &tmp);
    huge_t_delete(&tmp);
}

// b cannot be bigger than UINT_INTERNAL_BASE otherwise wrong calculation
uint_internal_t huge_t_calc_module(const huge_t a, const uint_internal_t b)
{
    __huge_t_ptr_check(&a);

    uint_internal_t borrow = 0;
    uint_internal_t remainder = 0;
    for (size_t i = 0; i < a.len; i++)
    {
        size_t fromend = a.len - i - 1;
        uint_internal_t sum = borrow + a.chunks[fromend];
        if (sum >= b)
        {
            remainder = sum % b;
            borrow = remainder * UINT_INTERNAL_BASE;
        }
        else if (sum < b && sum > 0)
        {
            borrow = sum * UINT_INTERNAL_BASE;
            remainder = sum;
        }
    }
    return remainder;
}

/*MATH OPERATIONS END*/
/*INPUT START*/
char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char to_char(const uint_internal_t decimal) {
    return digits[decimal];
}

uint_internal_t to_decimal(const char digit) {
    char*find = strchr(digits, digit);
    return (uint_internal_t)(find - digits);
}

// numerical system
huge_t parse_str(const char* str, const uint_internal_t num_sys) {
    size_t len = strlen(str);
    
    huge_t result;
    huge_t tmp;
    huge_t num_digit; // numerical digit

    huge_t_init(&num_digit, 1, 1);
    huge_t_init_zero(&result, 0);
    huge_t_init_zero(&tmp, 0);
    for (int i = len - 1; i >= 0; --i)
    {
        // convert num in numericalSystem to decimal 
        char digit = str[i];
        uint_internal_t decimal = to_decimal(digit);

        // multiply numerical digit on numerical system to get value in decimal
        huge_t_multiply(&tmp, num_digit, decimal);
        huge_t_add_assign(&result, tmp);
        huge_t_multiply_assign(&num_digit, num_sys);
    }
    huge_t_delete(&tmp);
    huge_t_delete(&num_digit);

    return result;
}

char* to_str(huge_t decimal, uint_internal_t num_sys) {
    char tmp[MAX_CHAR_INPUT * 10];
    size_t result_len = 0;
    huge_t n;
    huge_t_init(&n, 0, 0);
    huge_t_copy(&n, &decimal);

    while (!huge_t_is_zero(n)) {
        uint_internal_t remainder = huge_t_calc_module(n, num_sys);
        char digit = to_char(remainder);

        tmp[result_len] = digit;
        result_len++;
        huge_t_divide_assign(&n, num_sys);
    }
    huge_t_delete(&n);
    // reverse result string
    char* result = (char*)malloc((size_t)(result_len + 1)); // + 1 for \0 character
    for (size_t i = 0; i < result_len; i++)
    {
        result[i] = tmp[result_len - i - 1]; // - 1 because result len is not index it is size of @tmp
    }
    result[result_len] = '\0';
    return result;
}

/*INPUT END*/

int main()
{
    int m = 0;
    int k = 0;
    scanf("%d %d", &m, &k);

    char input_str[MAX_CHAR_INPUT + 1];
    scanf("%s", input_str);
    input_str[MAX_CHAR_INPUT] = '\0';
    huge_t num = parse_str(input_str, m);
    char* output_str = to_str(num, k);

    printf("%s\n", output_str);
    free(output_str);
    huge_t_delete(&num);
    return 0;
}