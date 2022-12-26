#include <iostream>
using namespace std;
//https://www.eolymp.com/ru/problems/8962
void swap(int& a, int& b) {
    int tmp{};
    tmp = a;
    a = b;
    b = tmp;
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

    int biggestIndex{};
    int biggestValue{};
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
        if (i == 0) {
            biggestIndex = 0;
            biggestValue = arr[i];
        }
        if (arr[i] >= biggestValue) {
            biggestIndex = i;
            biggestValue = arr[i];
        }
    }

    swap(arr[biggestIndex], arr[size-1]);
    printArr(arr, size);
}