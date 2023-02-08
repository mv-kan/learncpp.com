#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    auto *res{new Resource{}};
    std::shared_ptr<Resource> ptr1{res};
    std::shared_ptr<Resource> ptr2{ptr1};

    return 0;
}