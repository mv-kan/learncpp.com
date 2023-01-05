#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602651

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

void solve(int** arrPointer, int size) {
    int* solvedArr = malloc(size * sizeof(int));
    int* arr = *arrPointer;

    int range = size / 2;
    int startOfOdd = 1;
    int startOfEven= size - range;

    for (int i = 0; i < size; i++)
    {
        if (i == 0) {
            solvedArr[i] = arr[i];
            continue;
        }
        if (i % 2 == 0) {
            solvedArr[i] = arr[startOfOdd];
            startOfOdd++;
        } else {
            solvedArr[i] = arr[startOfEven];
            startOfEven++;
        }
    }

    free(arr);

    *arrPointer = solvedArr;
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

    solve(&arr, size);

    printArr(arr, size);

    //

    free(arr);
}