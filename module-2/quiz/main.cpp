#include <iostream>
#include "io.h"

int main() 
{
    std::cout << "enter num: ";
    int num{readNumber()};
    writeAnswer(num);
}