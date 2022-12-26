#include <iostream>
using namespace std;
// https://www.eolymp.com/ru/submissions/12554374
int main()
{
    int *arr;
    int size;

    cin >> size;
    if (!(size <= 100 && size >= 1))
    {
        return 1;
    }

    arr = new int[size];

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
        arr[i] = arr[i] % 100;
    }
    if (size / 2 == 0)
    {
        cout << "NO\n";
    }
    else
    {
        cout << size / 2 << endl;
        for (int i = 1; i < size; i += 2)
        {
            cout << arr[i] << ' ';
        }
        cout << endl;
    }

    if (arr)
        delete[] arr;
}