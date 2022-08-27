#include<iostream>

int readNumber()
{
    int answer{};
    std::cin >> answer;
    return answer;
}

void writeAnswer(int x)
{
    std::cout << "your number is " << x << std::endl;
}
