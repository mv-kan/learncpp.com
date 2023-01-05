#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602466

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

void printArrCon(int* arr, int size, bool (*compare)(int)) {
    for (int i = 0; i < size; i++)
    {
        if (compare(arr[i]))
            printf("%d ", arr[i]);
    }
    printf("\n");
}

bool onlyNegatives(int n) {
    return n > 0;
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

    int numOfPositives = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0)
            numOfPositives++;
    }
    
    if (numOfPositives > 0) {
        printf("%d\n", numOfPositives);
        
        printArrCon(arr, size, onlyNegatives);

        printf("\n");
    } else {
        printf("NO");
    }
    
    free(arr);
}