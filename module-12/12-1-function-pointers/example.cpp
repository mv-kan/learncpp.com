#include <iostream>

int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

int add(int a, int b) {
    return a + b;
}

int main()
{
    // float (*ffnPtr)() {foo}; // error types are not matching
    int (*fnptr)(int, int){add};
    if (fnptr) {
        std::cout << fnptr(20,20) << std::endl;
    }


    return 0;
}