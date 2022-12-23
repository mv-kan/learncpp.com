#include <iostream>

int main() 
{
    int x{5};
    int y{10};

    // c style cast
    double d{(double)x / y};

    std::cout << d << std::endl;
    
    // c style cast like function 
    d = double(y) / x; 
    return 0;
}