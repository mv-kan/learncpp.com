#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>
using namespace std;

namespace item {
    enum ItemTypes {
        healthPotion,
        torch,
        arrow
    };
}

template<typename T, unsigned long int Size> 
int countTotalItems(const std::array<T, Size>& arr) {
    return std::reduce(arr.begin(), arr.end());
}

int main()
{
    std::array<int, 3> arr{2, 5, 10};

    std::cout << "Total num: " << countTotalItems(arr) << endl;
    std::cout << "Num of torches: " << arr.at(item::torch) << endl;


    // std::array arr{1, 2, 3, 4};

    // std::cout << std::reduce(arr.begin(), arr.end()) << '\n'; // 10

    // // If you can't use std::reduce, use std::accumulate. The 0 is the initial value
    // // of the result: (((0 + 1) + 2) + 3) + 4
    // std::cout << std::accumulate(arr.begin(), arr.end(), 0) << '\n'; // 10

    // std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    // std::shuffle(arr.begin(), arr.end(), mt);

    // for (int i : arr)
    // {
    //     std::cout << i << ' ';
    // }

    // std::cout << '\n';



    return 0;
}