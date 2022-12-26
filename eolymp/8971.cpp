#include <iostream>
using namespace std;
//https://www.eolymp.com/ru/problems/8971

int main() {
    int *arr;
    int size;

    cin >> size;

    arr = new int[size];

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < size; i++)
    {
        bool duplicate{false};
        for (int j = i-1; j >= 0; j--)
        {
            if (arr[i] == arr[j]) {
                duplicate = true;
            }
        }
        if (!duplicate)
            cout << arr[i] << ' ';
    }
    cout << endl;
    

    if (arr)
        delete[] arr;
}