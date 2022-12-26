#include <iostream>
using namespace std;
//https://www.eolymp.com/ru/submissions/12554268
int main() 
{
    int* arr;
    int size; 

    cin >> size; 
    if (!(size <= 100 && size >= 1)) {
        return 1;
    }

    arr = new int[size];

    int nNegative{};
    for (int i = 0; i < size; i++)
    {
        int& ref = arr[i];
        cin >> ref;
        if (ref < 0)
            nNegative++;
    }
    
    if (nNegative > 0) {
        cout << nNegative << endl;
        for (int i = size; i >= 0; i--)
        {
            if (arr[i] < 0)
                cout << arr[i] << ' ';
        }
        cout << endl;
    } else {
        cout << "NO\n";
    }

    if (arr)
        delete[] arr;
}