#include<iostream>
#include<iterator>

int main() {
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    int size{static_cast<int>(std::size(array))};

    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }
    
}