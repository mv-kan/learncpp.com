#include <iostream>

class IntPair {
    
public:
int a{-2};
    int b{-1};
    // IntPair() {}
    // IntPair(int n1, int n2): a(n1), b(n2) {

    // }
    void set(int n1, int n2) {
        a = n1;
        b = n2;
    }
    void print() const {
        std::printf("Pair(%d, %d)", a, b);
    }
};

int main() {
    IntPair p1;

    IntPair p2 {2,2};

    p1.print();
    std::cout <<"\n";
    p2.print();
    std::cout <<"\n";

}