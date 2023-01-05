#include <iostream>
#include <limits>
#include <functional>
// <PROJECT>
namespace coolinput
{
// include in namespace is TERRIBLE idea
// do not repeat
// QUESTION: why here this is not working
#include <iostream>
#include <limits>
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
            result = new T{obj};
            return result;
        }
    }

    template <>
    std::string *getInput()
    {
        std::string obj{};
        std::string *result{nullptr};
        std::getline(std::cin >> std::ws, obj);
        if (!std::cin)
        {
            std::cin.clear();
            return result;
        }
        else
        {
            result = new std::string{obj};
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
                // convert dynamic to static
                T staticResult{*result};
                delete result;
                return staticResult;
            }
        }
    }
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return a / b;
}

using ArithmFn = std::function<int(int, int)>;

ArithmFn getArithmFn(char oper) {
    switch (oper)
    {
    case '+':
        return add;
        break;
    case '-':
        return subtract;
        break;
    case '/':
        return divide;
        break;
    case '*':
        return multiply;
        break;
    default:
        return nullptr;
        break;
    }
}

int main() {
    int a{coolinput::pleaseEnter<int>("enter int a: ")};
    int b{coolinput::pleaseEnter<int>("enter int b: ")};
    char oper{};
    std::string operators{"+-*/"};
    while (operators.find(oper) == std::string::npos) {
        oper = coolinput::pleaseEnter<char>("enter operator (+, -, *, /): ");
    }
    std::function arithmFn{getArithmFn(oper)};
    std::cout << a << oper << b << '=' << arithmFn(a, b) << std::endl;
}