#include <iostream>

void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}