#include <iostream>
#include <cstdarg> 
// This method of keeping track of ellipsis params is THE WORST dont use it!
double findAverage(int count, ...)
{
    int sum{ 0 };

    std::va_list list;

    va_start(list, count);

    for (int arg{ 0 }; arg < count; ++arg)
    {
         sum += va_arg(list, int);
    }
    va_end(list);

    return static_cast<double>(sum) / count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
    std::cout << findAverage(7, 1, 2, 3, 4, 5, 6) << '\n';
    std::cout << findAverage(5, 1, 2, 3, 4, 5, 6) << '\n';


    return 0;
}