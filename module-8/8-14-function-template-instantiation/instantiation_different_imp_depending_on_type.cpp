#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x > y) ? x : y;
}

template<>
float max<float>(float x, float y) // the generated function max<int>(int, int)
{
    return x + y;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)
    std::cout << max(1.f, 2.f) << '\n';  // error, we didn't provide implementation of max<float>(float, float)

    return 0;
}