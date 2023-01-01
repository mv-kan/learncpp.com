#include <iostream>
#include <limits>
using namespace std;
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
template <typename T>
T *getInput()
{
    T obj{};
    T *result{nullptr};
    std::cin >> obj;
    if (!std::cin)
    {
        std::cin.clear();
        ignoreLine();
        return result;
    }
    else
    {
        ignoreLine();
        result = &obj;
        return result;
    }
}

template <typename T>
T pleaseEnter(std::string_view message)
{
    while (true)
    {
        std::cout << message;
        T *result{getInput<T>()};
        if (result != nullptr)
        {
            return *result;
        }
    }
}

struct Fraction {
    int numerator{};
    int denominator{1};
};

Fraction multiplyFrac(Fraction a, Fraction b) {
    return {a.numerator * b.numerator, a.denominator * b.denominator};
}

Fraction enterFraction() {
    int numerator{pleaseEnter<int>("enter numberator: ")};
    int denominator{pleaseEnter<int>("enter denominator: ")};
    return {numerator, denominator};
}

int main(){
    Fraction a{enterFraction()};
    Fraction b{enterFraction()};

    Fraction c{multiplyFrac(a, b)};
    cout << "Your fraction is: " << c.numerator<<'/' <<c.denominator << endl;
}