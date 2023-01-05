#include <iostream>

int fib(int n) {
    int a{0};
    int b{1};
    int c{};
    if (n == a)
        return a;
    if (n == b)
        return b;
    for (int i = 1; i < n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}


int main() {
    for (int count { 0 }; count < 13; ++count)
        std:: cout << fib(count) << ' ';
    std::cout << std::endl;
    return 0;
}