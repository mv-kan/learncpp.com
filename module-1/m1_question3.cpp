#include <iostream>

int main()
{
    int a{}, b{};
    
    std::cout << "enter number a: ";
    std::cin >> a;
    
    std::cout << "enter number b: ";
    std::cin >> b;

    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << a << " - " << b << " = " << a - b << std::endl;
}