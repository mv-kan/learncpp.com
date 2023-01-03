#include<iostream>
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
        // QUESTION: this is messed up, earlier I just saved address of obj to result 
        // IT WORKED!!! but it shouldn't.  
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
            // QUESTION: is it like viable solution, or bad practice? 
            delete result;
            return staticResult;
        }
    }
}
int main () {
    std::string_view arr[]{"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};

    std::string name {pleaseEnter<std::string>("Enter name: ")};
    for (const auto& i : arr)
    {
        if(i == name) {
            std::cout << name << " was found \n";
            return 0;
        }
    }
    std::cout << name << " was not found \n";

    
}