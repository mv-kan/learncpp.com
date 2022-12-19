#include <iostream>

void incrementAndPrint()
{
    static int s_value{1}; // static duration via static keyword. Initilizer executed once.  
    ++s_value; 
    std::cout << s_value << std::endl; 
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope. 

int main() 
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();
    return 0;
}