#include <iostream>
#include <functional>

struct Student {
    std::string name{};
    int points{};
};

int main()
{
    std::array<Student, 8> arr{
        {{"Albert", 3},
         {"Ben", 5},
         {"Christine", 2},
         {"Dan", 8}, // Dan has the most points (8).
         {"Enchilada", 4},
         {"Francis", 1},
         {"Greg", 3},
         {"Hagrid", 5}}};
    const auto mostPoints {[](const auto& a, const auto& b) {
        return a.points < b.points;
    }};
    const auto coolestStudent {std::max_element(arr.begin(), arr.end(), mostPoints)};
    if (coolestStudent != arr.end())
        std::cout << "name: " << coolestStudent->name << "\tpoints: " << coolestStudent->points << std::endl;
}