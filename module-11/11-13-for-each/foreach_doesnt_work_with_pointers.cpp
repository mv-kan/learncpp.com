#include <iostream>

int sumArray(const int array[]) // array is a pointer
{
    int sum{ 0 };

    for (auto number : array) // compile error, the size of array isn't known
    {
        sum += number;
    }

    return sum;
}

int main()
{
     constexpr int array[]{ 9, 7, 5, 3, 1 };

     std::cout << sumArray(array) << '\n'; // array decays into a pointer here

     return 0;
}