#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602551

void inputArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        arr[i] = arr[i] % 100;
    }
}

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}   

void printArrEvenIndex(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 1)
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
        exit(1);
    }

    inputArr(arr, size);


    if (size / 2 == 0)
    {
        printf("NO\n");
    }
    else
    {
        printf("%d\n", size / 2);
        
        printArrEvenIndex(arr, size);

        printf("\n");

    }

    free(arr);
}