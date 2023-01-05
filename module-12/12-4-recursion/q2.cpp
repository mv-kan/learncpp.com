#include<iostream>

int sumOfDigits(int n) {
    if (n <= 0)
        return 0;
    int sum{sumOfDigits(n / 10) + n % 10};
    return sum;
}


int main() {
    std::cout << sumOfDigits(93477) << std::endl;
    std::cout << 9 / 10 << std::endl;

    return 0;
}