#include <iostream>
using namespace std;
//https://www.eolymp.com/ru/problems/8963
void swap(int& a, int& b) {
    int tmp{};
    tmp = a;
    a = b;
    b = tmp;
}
void pushToStart(int*arr, int size, int value) {
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value) {
            int offset{i};
            for (int j = i; j >= 0; j--)
            {
                swap(arr[offset], arr[j]);
                offset = j;
            }
        }
    }
    
}

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main() {
    int *arr;
    int size;

    cin >> size;

    arr = new int[size];

    int smallest{};
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
        if (i == 0) {
            smallest = arr[i];
        }
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    pushToStart(arr, size, smallest);
    printArr(arr, size);
}