#include <iostream>


int main() 
{
    char letter{'a'};
    while (letter <= 'z')
    {
        std::cout << letter << '\t';
        letter++;
        if (letter % 5 == 0)
            std::cout << '\n';
    }
    std::cout << '\n';
}