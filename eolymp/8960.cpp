#include <iostream>
using namespace std;
// https://www.eolymp.com/ru/submissions/12554503
int main()
{
    int *arr;
    int size;

    cin >> size;

    arr = new int[size];

    int biggest{};
    int smallest{};
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
        if (i == 0) {
            smallest = arr[i];
            biggest = arr[i];
        }
        if (arr[i] > biggest)
            biggest = arr[i];
        
        if (arr[i] < smallest)
            smallest = arr[i];
    }
    
    int sum{};
    for (int i = 0; i < size; i++)
    {
        sum += arr[i] != smallest && arr[i] != biggest ? arr[i] : 0; 
    }
    cout << sum << endl;
    if (arr)
        delete[] arr;
}