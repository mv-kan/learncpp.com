#include <iostream>

using Degrees = double;
using Radiants = double;
namespace constants
{
    inline constexpr double pi { 3.14159 };
}

Radiants convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    Degrees degrees{};
    std::cin >> degrees;

    Radiants radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}