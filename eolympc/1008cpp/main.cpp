#include <iostream>
#include "huge.h"

#define HUGE_CAPACITY 1000
#define MAX_CHAR_INPUT 1000

int main() {
    Huge h{1000000, HUGE_CAPACITY};

    h.Divide(36);
    h.Print();
    std::cout << h.CalcModule(36);
}