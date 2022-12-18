#include <iostream>
#include <string>
int main() {
    using namespace std::literals;
    std::string name{};
    std::cout << "Enter name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Your name is: " << name << std::endl;
    
    // s is literals enabled by using namespace std::literals
    std::cout << "Lenth of your name: "s << name.length() << std::endl;
    return 0;
}