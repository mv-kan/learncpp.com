#include <iostream>

struct Foo
{
    short a {};
    int b {};
    double c {};
};

int main()
{
    std::cout << "The size of Foo is " << sizeof(Foo) << '\n';

    return 0;
}