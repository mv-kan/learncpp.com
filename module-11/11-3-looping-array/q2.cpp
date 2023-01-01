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

using namespace std;

int main() {
    int inputed{};
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
    do {
        inputed = pleaseEnter<int>("Entere number between 1 and 9: ");
    } while(inputed < 1 || inputed > 9);
    int size{static_cast<int>(std::size(array))};

    for (int i = 0; i < size; i++)
    {
        if (array[i] == inputed) {
            std::cout << "The number " << inputed << " has index " << i << std::endl;
            break;
        }
    }
}