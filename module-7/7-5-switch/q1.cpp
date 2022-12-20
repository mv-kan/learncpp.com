#include <iostream>

int calculate(int a, int b, char oper)
{
    switch (oper)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '/':
        return a / b;
        break;
    case '*':
        return a * b;
        break;
    case '%':
        return a % b;
        break;
    default:
        std::cout << "error!" << std::endl;
        return 0;
        break;
    }
}

int main () 
{
    std::cout << calculate(2,3,'+') << std::endl;
    std::cout << calculate(2,3,'/') << std::endl;
    std::cout << calculate(2,3,'%') << std::endl;
    std::cout << calculate(2,3,'$') << std::endl;
    std::cout << calculate(2,3,'/') << std::endl;
}