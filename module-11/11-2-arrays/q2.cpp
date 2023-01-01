#include <iostream>
using namespace std;

namespace animal {
    enum Animal {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        numOfAnimals
    };
}

int main() {
    int legs[animal::numOfAnimals]{2, 4, 4, 4, 2, 0};

    cout << legs[animal::cat] << endl;
}