#include <iostream>

void foo()
{
    foo();
    std::cout << "hi";
}

int main()
{
    foo();

    return 0;
}