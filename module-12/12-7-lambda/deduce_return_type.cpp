#include <iostream>

int main()
{
    auto divide{[](int x, int y, bool intDivision) { // note: no specified return type
        if (intDivision)
            return x / y; // return type is int
        else
            return static_cast<double>(x) / y; // ERROR: return type doesn't match previous return type
    }};

    std::cout << divide(3, 2, true) << '\n';
    std::cout << divide(3, 2, false) << '\n';

    auto divide{[](int x, int y, bool intDivision) -> double { 
        if (intDivision)
            return x / y; 
        else
            return static_cast<double>(x) / y;
    }};
    
    return 0;
}