#include <iostream>
// selection sort

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    
}

int main() {
   
    int arr[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };

    const int size{9};
    int iterations{};
    // sort all array
    for (int i = 0; i < size; i++)
    {
        int tmpIndex{};

        // sort one element
        bool swaped{false};
        for (int j = 0; j < size - i - 1; j++)
        {
            iterations++;

            if (arr[tmpIndex] > arr[j + 1]) {
                std::swap(arr[tmpIndex], arr[j + 1]);
                swaped = true;
            }
            tmpIndex = j;
        }
        if (!swaped) {
            break;
        }
    }
    std::cout << "iterations: " << iterations << std::endl;   
    printArr(arr, size);
}