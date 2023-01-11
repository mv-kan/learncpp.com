#include <iostream>
#include <vector>
#include <limits>
#include <random>
namespace coolinput
{
    // this is required inlcudes, if you dont have them please include this lines below

    // #include <iostream>
    //

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

#include <algorithm>

int getRandNum(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution die{min, max};
    return die(mt);
}
void printArr(const std::vector<int> &arr)
{
    for (auto n : arr)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
const int multiplierFrom{2};
const int multiplierTo{4};
const int maxWrongAnswer{4};
int main()
{
    // get all required data from user
    int base{coolinput::pleaseEnter<int>("Start where? ")};
    int numOfSquares{coolinput::pleaseEnter<int>("How many? ")};

    if (numOfSquares < 0)
    {
        std::cout << "how many cannot be negative" << std::endl;
        exit(0);
    }
    int squareMultiplier{getRandNum(multiplierFrom, multiplierTo)};

    // generate numbers for array
    std::vector<int> arr(static_cast<size_t>(numOfSquares), 0);

    int baseIncrement{base};
    for (size_t i = 0; i < arr.size(); ++i)
    {
        arr.at(i) = baseIncrement * baseIncrement * squareMultiplier;
        ++baseIncrement;
    }

    // start game
    // show user multiplier
    std::printf("I generated %d square numbers. Do you know what each number is after multiplying it by %d?\n", numOfSquares, squareMultiplier);

    // prompt user
    while (true)
    {
        int userGuess{coolinput::pleaseEnter<int>("> ")};
        // std::find in array user's answer
        auto it{std::find(arr.begin(), arr.end(), userGuess)};
        // if not found: user lost
        if (it == arr.end())
        {
            auto closeEnough{std::find_if(arr.begin(), arr.end(), 
            [userGuess](const auto& a)
            { 
                return abs(a - userGuess) < maxWrongAnswer;  
            })};
            if (closeEnough == arr.end())
                std::printf("%d is wrong!\n", userGuess);
            else 
                std::printf("%d is wrong! Try %d next time.\n", userGuess, *closeEnough);
            exit(0);
        }
        // if ok: delete num from array and show num of remaining numbers to guess
        else
        {
            arr.erase(it);
            if (arr.size() == 0) {
                std::cout << "You have won!!!" << std::endl;
                exit(0);
            }
            std::printf("Nice! %zu number(s) left.\n", arr.size());
            
        }
    }
}