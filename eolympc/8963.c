#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602636

void swap(int* a, int* b) {
    int tmp=0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void pushToStart(int*arr, int size, int value) {
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value) {
            int offset=i;
            for (int j = i; j >= 0; j--)
            {
                swap(&arr[offset], &arr[j]);
                offset = j;
            }
        }
    }
    
}

void inputArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}   


int main() 
{
    int* arr = NULL;
    int size = 0;

    scanf("%d", &size);

    arr = (int*) malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Mem is not allocated\n");
        exit(0);
    }

    inputArr(arr, size);

    // solution

    int smallest=0;
    for (int i = 0; i < size; i++)
    {
        if (i == 0) {
            smallest = arr[i];
        }
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    pushToStart(arr, size, smallest);
    printArr(arr, size);

    //

    free(arr);
}