#include <iostream>
using namespace std;
//https://www.eolymp.com/ru/submissions/12554231
int main() 
{
    int* arr;
    int size; 

    cin >> size; 
    if (!(size <= 100 && size >= 1)) {
        return 1;
    }

    arr = new int[size];

    int nPositive{};
    for (int i = 0; i < size; i++)
    {
        int& ref = arr[i];
        cin >> ref;
        if (ref > 0)
            nPositive++;
    }
    
    if (nPositive > 0) {
        cout << nPositive << endl;
        for (int i = 0; i < size; i++)
        {
            if (arr[i] > 0)
                cout << arr[i] << ' ';
        }
        cout << endl;
    } else {
        cout << "NO\n";
    }

    if (arr)
        delete[] arr;
}