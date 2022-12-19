#include <iostream>

inline namespace v1 { // declare an inline namespace named v1
    void doSomething() {
        std::cout << "1v\n";
    }
}


namespace v2 {  // declare a normal namespace named v2
    void doSomething() {
        std::cout << "2v\n";
    }
}

int main()
{
    v1::doSomething(); // calls the v1 version of doSomething()
    v2::doSomething(); // calls the v2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is v1)
    return 0;
}