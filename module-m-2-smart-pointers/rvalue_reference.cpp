#include <iostream>
#include <memory>
void fun(const int &lref) // l-value arguments will select this function
{
    std::cout << "l-value reference to const: " << lref << '\n';
}

void fun(int &&rref) // r-value arguments will select this function
{
    std::cout << "r-value reference: " << rref << '\n';
}

int main()
{
    int x{5};
    int&&ref{10};
    fun(x); // l-value argument calls l-value version of function
    fun(5); // r-value argument calls r-value version of function
    fun(ref);
    std::unique_ptr<int>ptr{new int};
    return 0;
}