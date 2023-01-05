#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602680

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
    
    for (int i = 0; i < size; i++)
    {
        bool duplicate = false;
        for (int j = i-1; j >= 0; j--)
        {
            if (arr[i] == arr[j]) {
                duplicate = true;
            }
        }
        if (!duplicate)
            printf("%d ", arr[i]);
    }
    printf("\n");

    //

    free(arr);
}