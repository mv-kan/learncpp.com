#include <iostream>

const double gravity{9.8};

double calcFallenDistance(size_t seconds) {
    double distanceFallen = gravity * seconds * seconds / 2;
    return distanceFallen;
}

int main() {
    const size_t seconds{10};
    double inputMeters{};
    std::cout << "Enter meters: ";
    std::cin >> inputMeters;

    for (size_t i = 0; i < seconds + 1; i++)
    {
        double fallenMeters{calcFallenDistance(i)};
        double remainingMeters{inputMeters - fallenMeters};
        if (remainingMeters < 0)
        {
            remainingMeters = 0;
        }
        std::cout << "at " << i << " seconds the ball is at height: " << remainingMeters << std::endl;
    }
    
    return 0;
}