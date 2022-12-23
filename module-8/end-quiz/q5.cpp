#include <iostream>

// write your add function template here
template<typename T> 
T add(T a, T b) 
{
    return a + b;
}

template<typename T> 
T mult(T a, T b) 
{
    return a * b;
}

template<typename T, typename T2> 
auto sub(T a, T2 b) 
{
    return a - b;
}

int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';
    
    std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, static_cast<double>(3)) << '\n';

    std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';
	std::cout << sub(4, 1) << '\n';

	return 0;
}