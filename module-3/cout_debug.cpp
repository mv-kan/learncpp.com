#include <iostream>

int getValue() 
{
    std::cerr << "getValue() called\n";
    return 5;
}

int main ()
{
    std::cerr << "main() called\n"; 
    std::cout << getValue();
    return 0;
}