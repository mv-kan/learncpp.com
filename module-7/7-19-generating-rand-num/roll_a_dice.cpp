#include <iostream>
#include <random>
#include <chrono>
int main() 
{
    std::mt19937 mt{static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())};
    // Create a reusable random number generator that generates uniform numbers between 1 and 6
    std::uniform_int_distribution die6{1,6};

    for (int i = 0; i < 40; i++)
    {
        std::cout << die6(mt) << '\t';
        if (i % 5 == 0)
            std::cout << '\n';
    }
    return 0; 
}