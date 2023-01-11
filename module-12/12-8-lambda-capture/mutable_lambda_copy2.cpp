#include <iostream>
#include <functional>
// std::function creates copy of lambda 
// this is why output is just 1 and increamenting is not occuring at a first glance
void myInvoke(const std::function<void()> &fn)
{
    fn();
}

int main()
{
    int i{0};

    // Increments and prints its local copy of @i.
    auto count{[i]() mutable
               {
                   std::cout << ++i << '\n';
               }};
    // bad!!!
    myInvoke(count);
    myInvoke(count);
    myInvoke(count);
    // good!!!
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));

    return 0;
}