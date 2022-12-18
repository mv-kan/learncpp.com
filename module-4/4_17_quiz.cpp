#include <iostream>

int main() {
    std::string fullname{};
    int age{};

    std::cout << "Enter full name: "; 
    std::getline(std::cin >> std::ws, fullname);
    std::cout << "Enter age: ";
    std::cin >> age; 

    std::cout << "Your age + length of your name = " << static_cast<int>(fullname.length()) + age << std::endl;

    return 0;
}