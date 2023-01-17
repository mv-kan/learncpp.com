#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
/*
RULES:
1. there is not huge_t dynamically allocated, they are always stack vars (but not fragments in huge_t)
2. Every huge_t object has capacity of HUGE_T_CAPACITY
*/
// please use just 10-base base
// don't fuck with binary
#define UINT_INTERNAL_BASE 1000
#define HUGE_T_CAPACITY 100
#define MAX_CHAR_INPUT 1000
typedef uint16_t uint_internal_t;

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

// to 10-base value if UINT_INTERNAL_BASE is 10-base
// formating depends on UINT_INTERNAL_BASE
// if you were to change UINT_INTERNAL_BASE then you have to change this function too
void huge_t_print(const huge_t huge)
{
    __huge_t_ptr_check(&huge);
    for (size_t i = 0; i < huge.len; i++)
    {
        // print from end to start
        printf("%03d", huge.chunks[huge.len - i - 1] % UINT_INTERNAL_BASE);
    }
    if (huge.len == 0)
    {
        printf("%03d", 0);
    }
    printf("\n");
}

void huge_t_print_true(const huge_t huge)
{
    __huge_t_ptr_check(&huge);
    for (size_t i = 0; i < huge.len; i++)
    {
        // print from end to start
        printf(" %d ", huge.chunks[huge.len - i - 1]);
    }
    if (huge.len == 0)
    {
        printf(" %d ", 0);
    }
    printf("\n");
}

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

void huge_t_copy(huge_t *const ptr, huge_t *const copy)
{
    __huge_t_ptr_check(ptr);
    __huge_t_ptr_check(copy);
    huge_t_set_zero(ptr);

    ptr->len = copy->len;
    for (size_t i = 0; i < ptr->len; i++)
    {
        ptr->chunks[i] = copy->chunks[i];
    }
}
/*BASIC STUFF END*/

/*MATH OPERATIONS START*/
// void __huge_t_len_equal(const huge_t a, const huge_t b) {
//     if (a.len != b.len) {

//     }
// }

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
    
    if (carry > 0 && (ptr->len < ptr->capacity)) {
        ptr->chunks[ptr->len] = carry;
        ptr->len++;
    }
}



// void huge_t_divide(huge_t *const ptr, const huge_t a, const uint_internal_t b) {

// }

int main()
{
    huge_t a, result;
    huge_t_init(&a, 123321, 2);
    huge_t_init(&result, 0, 2);

    huge_t_multiply(&result, a, 2);

    huge_t_print_true(result);
    return 0;
}