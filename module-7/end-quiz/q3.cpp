#include <iostream>
#include <random>
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

namespace guessrand
{
    std::mt19937 mt{std::random_device{}()};

    int get(int min, int max)
    {
        std::uniform_int_distribution die{min, max}; // we can create a distribution in any function that needs it
        return die(mt);                              // and then generate a random number from our global generator
    }
}
bool playGame(int min, int max, size_t tries)
{
    if (min > max)
    {
        std::cout << "lol man, min can not be bigger than max" << std::endl;
        return false;
    }
    int guessNum{guessrand::get(min, max)};
    std::cout << "lest play, I choose num from " << min << " to " << max << std::endl;
    for (size_t i = 0; i < tries; i++)
    {
        /* code */
        int num{};
        while (num > max || num < min)
        {
            num = pleaseEnter<int>("guess #" + std::to_string(i + 1) + ": ");
        }
        if (num > guessNum)
            std::cout << "guess too big\n";
        else if (num < guessNum)
            std::cout << "guess too small\n";
        else
        {
            std::cout << "You won!!\n";
            return true;
        }
    }
    std::cout << "You lost, num is " << guessNum << std::endl;
    return false;
}
void gameRun(int min, int max, size_t tries)
{
    char ans{};
    do
    {
        bool won{playGame(min, max, tries)};

        if (won)
        {
            while (ans != 'q' && ans != 'n')
            {
                ans = pleaseEnter<char>("Again? (y/n): ");
            }
        }
    } while (ans == 'q');
}

int main()
{
    gameRun(1, 100, 7);
    return 0;
}
