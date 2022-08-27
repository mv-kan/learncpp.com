#include <iostream>

int main() 
{
    std::cout << "input number: ";
    int x{};

    std::cin >> x;

    std::cout << "the double of num: " << x * 2 << std::endl;
    std::cout << "the triple of num: " << x * 3 << std::endl;
}