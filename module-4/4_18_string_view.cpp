#include <iostream>

void print(std::string_view sv) 
{
    std::cout << sv << std::endl;
}

void printString(std::string s) 
{
    std::cout << s << std::endl;
}

int main()
{
    std::string_view sv{"Something"};
    print(sv);
    printString(static_cast<std::string>(sv));
}