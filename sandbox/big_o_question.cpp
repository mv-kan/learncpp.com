#include <iostream>
// selection sort

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    
}
void selectionSort(int * arr, int size) {
    for (int i = 0; i < size; i++)
    {
        // 
        int lowestIndex{i};
        for (int j = i; j < size; j++)
        {
            if (arr[lowestIndex] > arr[j]){
                lowestIndex = j;
            }
        }
        std::swap(arr[i], arr[lowestIndex]);
    }
}

int binarySearch(const int* array, int target, int min, int max)
{
    int midpoint{(min + max) / 2};
    
    if (target > array[midpoint]) {
        min = midpoint;
    } else if (target < array[midpoint]) {
        max = midpoint;
    } else {
        return midpoint;
    }

    // min == max                           is not found, because we come so close and didn't return any value, it means there is not any value equel to target
    // midpoint == min && max - min == 1    we came to midpoint is min and max and min really close and check in this iteration didn't find target, thus no element in array
    if ((midpoint == min && max - min == 1) || min == max)
        return -1;
    return binarySearch(array, target, min, max);
}

int main() {
    const int size{5};
    int arr[5]{20, 30, 10, 5, 12};
    selectionSort(arr, size);
    printArr(arr, size);
    std::cout << "20 has index of "<< binarySearch(arr, 20, 0, size) << std::endl;
}
