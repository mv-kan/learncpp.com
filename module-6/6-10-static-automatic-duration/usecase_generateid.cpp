#include <iostream>

int generateID() 
{
    static int s_itemID{0};
    return s_itemID++; 
}

int main() 
{
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << generateID() << std::endl;
    }
    return 0;  
}