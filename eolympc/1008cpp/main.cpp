#include <iostream>
#include "huge.h"

#define HUGE_CAPACITY 1000
#define MAX_CHAR_INPUT 1000

int main() {
    Huge h{10192837192, HUGE_CAPACITY};
    Huge h1{h};

    h = std::move(h1);
    h.Print();
    h1.Print();
}