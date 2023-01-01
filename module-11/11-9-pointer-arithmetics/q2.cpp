#include <iostream>
#include <iterator>

int* findValue(int* start, int* end, int value) {
    int size {static_cast<int>(end - start)};
    for (int i = 0; i < size; i++)
    {
        if (start[i] == value)
            return start;
    }
    return end;
}

int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };
    
    // Search for the first element with value 20.
    int* found{ findValue(std::begin(arr), std::end(arr), 20) };

    // If an element with value 20 was found, print it.
    if (found != std::end(arr))
    {
        std::cout << *found << '\n';
    }

    return 0;
}