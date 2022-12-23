#include <iostream>

int main() 
{
    short a{12};
    short b{32};

    std::cout << typeid(a + b).name() << '\t' << a+b << '\n';
    return 0;
}