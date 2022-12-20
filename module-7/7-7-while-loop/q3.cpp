#include <iostream>

int main() 
{
    int i{1}; 
    while(i <= 5)
    {
        int y{6 - i};
        while(y >= 1) {
            std::cout << y << '\t';
            y--;
        }
        std::cout << '\n'; 
        i++;
    }
}