#include <iostream>
#include <vector>
#include <array>
int main() {
    std::vector<int> arr(5);
    std::vector<bool> arrOfBits(32);

    for (auto i : arr)
    {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    
    for (auto i : arrOfBits)
    {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    arrOfBits.resize(16);
    for (auto i : arrOfBits)
    {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    
}