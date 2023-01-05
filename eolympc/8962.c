#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602551

void swap(int* a, int* b) {
    int tmp=0;
    tmp = *a;
    *a = *b;
    *b = tmp;
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

    int biggestIndex=0;
    int biggestValue=0;
    for (int i = 0; i < size; i++)
    {
        if (i == 0) {
            biggestIndex = 0;
            biggestValue = arr[i];
        }
        if (arr[i] >= biggestValue) {
            biggestIndex = i;
            biggestValue = arr[i];
        }
    }

    swap(&arr[biggestIndex], &arr[size-1]);
    printArr(arr, size);

    //

    free(arr);
}