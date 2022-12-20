#include <iostream>

int main() 
{
    const int grid{5};
    char fillerChar{' '};
    int i{1};
    while (i <= grid) 
    {
       int numberOfFillerChars{grid - i}; 
       int y{grid};
       while (y > 0) 
       {
            if (numberOfFillerChars > 0) 
            {
                std::cout << fillerChar << '\t';
                numberOfFillerChars--;
            } 
            else 
                std::cout << y << '\t';
            y--;
       }
       std::cout << '\n';
       i++; 
    }
}