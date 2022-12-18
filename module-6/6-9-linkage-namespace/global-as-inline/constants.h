#ifndef CONSTANTS_H
#define CONSTANTS_H
#include<iostream>
namespace constants 
{
    // linker's magic makes this inline variables into external linkage variables
    inline constexpr double pi {3.14};
    inline constexpr double myGravity {9.8};
    inline constexpr std::string_view constString{"My string"};
}

#endif