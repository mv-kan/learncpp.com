#include <iostream>

int main() 
{
    double n1{}, n2{};
    char oper{};
    std::cout << "enter number 1: ";
    std::cin >> n1;
    std::cout << "enter number 2: ";
    std::cin >> n2;


    std::cout << "choose operation (+, -, *, /): ";
    std::cin >> oper;

    switch (oper)
    {
    case '+':
        std::cout << n1 + n2 << std::endl;
        break;
    case '-': 
        std::cout << n1 - n2 << std::endl;
        break;
    case '*': 
        std::cout << n1 * n2 << std::endl;
        break;
    case '/': 
        std::cout << n1 / n2 << std::endl;
        break;
    default:
        std::cout << "invalid" << std::endl;
        break;
    }
}