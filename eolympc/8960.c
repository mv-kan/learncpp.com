#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
//https://www.eolymp.com/ru/submissions/12602609

void inputArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
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

    int biggest = 0;
    int smallest = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == 0) {
            smallest = arr[i];
            biggest = arr[i];
        }
        if (arr[i] > biggest)
            biggest = arr[i];
        
        if (arr[i] < smallest)
            smallest = arr[i];
    }
    
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        int toAdd = 0;
        if (!(arr[i] == smallest || arr[i] == biggest)) {
            toAdd = arr[i];
        }
        sum += toAdd; 
    }
    printf("%d\n", sum);

    //

    free(arr);
}