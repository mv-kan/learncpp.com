#include <iostream>
using namespace std;
//https://www.eolymp.com/ru/problems/8970

void solve(int*& arr, int size) {
    int* solvedArr = new int[size];

    int range{size / 2};
    int startOfOdd{1};
    int startOfEven{size - range};

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

    delete[] arr;

    arr = solvedArr;
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

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    solve(arr, size);

    printArr(arr, size);

    if (arr)
        delete[] arr;
}