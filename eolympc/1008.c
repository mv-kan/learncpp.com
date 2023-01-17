#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
/*
RULES:
there is not huge_t dynamically allocated, they are always stack vars (but not fragments in huge_t)

*/
// please use just 10-base base
// don't fuck with binary
#define UINT_INTERNAL_BASE 1000
#define HUGE_T_CAPACITY 100
#define MAX_INPUT 1000
typedef uint16_t uint_internal_t;

struct huge_s
{
    size_t len;
    size_t capacity;
    uint_internal_t *chunks;
};
typedef struct huge_s huge_t;

// calls everytime when init method is raised
void __huge_t_init(huge_t *const huge)
{
    if (huge)
    {
        size_t size_of_chunks = sizeof(uint_internal_t) * HUGE_T_CAPACITY;
        huge->chunks = malloc(size_of_chunks);
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
void huge_t_init_zero(huge_t *const huge)
{
    // __huge_t_init make it automatically zero
    __huge_t_init(huge);
}

void huge_t_init(huge_t *const huge, size_t value)
{
    __huge_t_init(huge);
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

// when deleted capacity is zero
void __huge_t_delete(huge_t *const huge)
{
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
    __huge_t_delete(huge);
}

// to 10-base value if UINT_INTERNAL_BASE is 10-base
void huge_t_print(const huge_t huge)
{
    for (size_t i = 0; i < huge.len; i++)
    {
        // print from end to start
        printf("%d", huge.chunks[huge.len - i - 1]);
    }
    printf("\n");
}

int main()
{
    huge_t huge;
    huge_t_init(&huge, 123123);
    huge_t_print(huge);
    return 0;
}