#include <iostream>
// selection sort

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    
}

int main() {
    const int size{5};
    int arr[5]{20, 30, 10, 5, 12};
    for (int i = 0; i < size; i++)
    {
        int highestIndex{i};
        for (int j = i; j < size; j++)
        {
            if (arr[highestIndex] < arr[j]){
                highestIndex = j;
            }
        }
        std::swap(arr[i], arr[highestIndex]);
    }
    printArr(arr, size);
}