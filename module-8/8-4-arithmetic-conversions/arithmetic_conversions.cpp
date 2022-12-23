#include <iostream>
#include <typeinfo> // for typeid

int main()
{
    int myvarint{2};
    double d{2.3};
    std::cout << typeid(myvarint).name() << std::endl;
    return 0;
}