#include <iostream>

void incrementAndPrint()
{
    int value{1}; // automatic duration by default 
    ++value; 
    std::cout << value << std::endl; 
    // value destroyed here 
}

int main() 
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();
    return 0;
}