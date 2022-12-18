#include <iostream>

int main() {
    unsigned short x{65535};
    std::cout << "x was: " << x << '\n';
    x = 65536;
    std::cout << "x is now: " << x << '\n';
    x = 65537;
    std::cout << "x is now: " << x << '\n';

    return 0; 
}