#include <iostream>

int sumTo(int n) 
{
    int result{};
    for (int i = 0; i <= n; ++i)
    {
       result += i; 
    }
    return result;
}
int main() 
{
    std::cout << sumTo(5) << std::endl;
}