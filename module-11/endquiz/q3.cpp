#include <iostream>

void myswap(int& a, int& b) {
    int tmp{a};
    a = b;
    b = tmp;
}

int main() {
    int a{100};
    int b{5};
    std::cout << a << "  " << b << std::endl; 
    myswap(a, b);
    std::cout << a << "  " << b << std::endl; 
}