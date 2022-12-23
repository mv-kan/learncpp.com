#include<iostream>

int main()
{
    size_t size{5};
    int*ptr{new int[size]};

    for (size_t i = 0; i < size; i++)
    {
        std::cout << ptr[i] << std::endl;
        /* code */
    }
    
    delete[] ptr;
    int*ptrvar{new int{10}};
    std::cout << *ptrvar << std::endl;
    delete ptrvar;
    return 0;
}