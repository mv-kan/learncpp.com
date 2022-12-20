#include <iostream>
#include <random>

int main()
{
    std::mt19937 mt;
    for (int i = 0; i < 40; i++)
    {
        std::cout << mt() << '\t';
        if (i % 5 == 0)
            std::cout << '\n';
    }
    return 0;
    
}