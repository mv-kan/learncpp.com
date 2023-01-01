#include <iostream>

void printEmployee(int id, int age, double wage)
{
    std::cout << "ID:   " << id << '\n';
    std::cout << "Age:  " << age << '\n';
    std::cout << "Wage: " << wage << '\n';
}

int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    printEmployee(id, age, wage);

    return 0;
}