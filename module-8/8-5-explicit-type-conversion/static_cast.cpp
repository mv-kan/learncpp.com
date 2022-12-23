#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << c << ' ' << static_cast<int>(c) << '\n'; // prints a 97
    
    // explicit narrowing conversions 
    int i{90};
    c = static_cast<char>(i);
    std::cout << c  << '\n'; // prints a 97
    return 0;
}