#include <functional>
#include <iostream>

int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

int too(int a) {
    return a;
}

int main()
{
    std::function<int()> fcnPtr{ &foo }; // declare function pointer that returns an int and takes no parameters
    fcnPtr = &goo; // fcnPtr now points to function goo
    std::cout << fcnPtr() << '\n'; // call the function just like normal

    std::function<int(int)> fnPtr{ too }; // declare function pointer that returns an int and takes no parameters
    std::cout << fnPtr(10) << '\n'; // call the function just like normal

    // in Cpp 17 we can use CTAD (class template argument deduction)
    std::function fn{too};
    std::cout << fn(100) << '\n';
    return 0;
}