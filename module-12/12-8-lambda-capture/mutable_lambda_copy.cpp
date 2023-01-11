#include <iostream>

int main()
{
    int i{0};

    // Create a new lambda named count
    auto count{[i]() mutable
               {
                   std::cout << ++i << '\n';
               }};

    count(); // invoke count: 1

    // auto &otherCount{count}; // create a reference of count
    auto otherCount{count}; // create a copy of count

    // invoke both count and the copy
    count(); // : 2
    otherCount(); // : 2 , because it is not count it is copy of count

    return 0;
}