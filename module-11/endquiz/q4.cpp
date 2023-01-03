#include <iostream>

void printStr(char* begin) {
    for (char* i = begin; *i != '\0'; i++)
    {
        std::cout << *i;
    }
}

int main() {
    char str[]{"Hello"};
    printStr(str);
    std::cout << std::endl;
}