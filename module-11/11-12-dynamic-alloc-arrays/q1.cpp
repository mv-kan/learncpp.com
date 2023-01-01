#include <algorithm> 
#include <iostream>
#include <string>
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
std::string* getInput()
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
        T* result{getInput<T>()};
    
        if (result != nullptr)
        {
            // convert dynamic to static
            T staticResult{*result};
            delete result;
            return staticResult;
        }
    }
}

void printNames(std::string* begin, std::string* end) {
    for (std::string* i = begin; i != end; i++)
    {
        std::cout << *i << std::endl;
    }    
}
 
int main() {
    int size { pleaseEnter<int>("How many names would you like to enter? ")};

    std::string* arr{new std::string[size]};
    for (int i = 0; i < size; i++)
    {
        arr[i] = pleaseEnter<std::string>("Enter name #" + std::to_string(i) + ": ");
    }
    // !!!
    std::sort(arr, arr + size);

    printNames(arr, arr + size);

    if (!arr)
        delete[] arr;
}