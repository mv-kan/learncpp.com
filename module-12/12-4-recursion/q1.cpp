#include <iostream>

int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    for (int i = 1; i <= 7; i++)
    {
        std::cout << factorial(i) << std::endl;
    }
    
    return 0;
}