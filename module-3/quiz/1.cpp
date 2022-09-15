#include <iostream>

int readNumber(int x)
{
    std::cout << "Please enter a number: ";
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The sum is: " << x << '\n';
}

int main()
{
    int x{}, y{};
    x = readNumber(x);
    y = readNumber(y);
    writeAnswer(x + y);

    return 0;
}