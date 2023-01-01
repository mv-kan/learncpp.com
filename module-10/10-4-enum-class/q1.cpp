#include <iostream>

enum class Animal {
    pig,
    chicken, 
    goat,
    cat, 
    dog, 
    duck
};

constexpr std::string_view getAnimalName(Animal animal) {
    using enum Animal;

    switch (animal)
    {
    case pig:
        return "pig";
        break;
    case chicken:
        return "chicken";
        break;
    case goat:
        return "goat";
        break;
    case cat:
        return "cat";
        break;
    case dog:
        return "dog";
        break;
    case duck:
        return "duck";
        break;
    default:
        return "undefined_animal";
        break;
    }
}

constexpr int getNumberOfLegs(Animal animal) {
    using enum Animal;

    switch (animal)
    {
    case pig:
        return 4;
        break;
    case chicken:
        return 2;
        break;
    case goat:
        return 4;
        break;
    case cat:
        return 4;
        break;
    case dog:
        return 4;
        break;
    case duck:
        return 2;
        break;
    default:
        return -1;
        break;
    }
}

int main() {
    Animal pet{Animal::pig};
    std::cout << getAnimalName(pet) << " has this number of legs: " << getNumberOfLegs(pet) << std::endl;
}