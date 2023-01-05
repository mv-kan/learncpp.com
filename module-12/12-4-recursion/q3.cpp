#include <iostream>

void convertToBin(int a) {
    uint n{static_cast<uint>(a)};
    if (n == 0)
        return;
    convertToBin(n / 2);
    std::cout << n % 2;
}

int main() {
    convertToBin(-148);
    std::cout << std::endl;
    return 0;
}