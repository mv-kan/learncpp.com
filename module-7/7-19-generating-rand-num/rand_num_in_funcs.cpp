#include <iostream>
#include <random> // for std::mt19937 and std::random_device


namespace myrand 
{
    std::mt19937 mt{std::random_device{}()}; 

    int get(int min, int max) 
    {
        std::uniform_int_distribution die{ min, max }; // we can create a distribution in any function that needs it
		return die(mt); // and then generate a random number from our global generator
    }
}

int main()
{
	std::cout << myrand::get(1, 6) << '\n';
	std::cout << myrand::get(1, 10) << '\n';
	std::cout << myrand::get(1, 20) << '\n';

	return 0;
}