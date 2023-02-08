#include <iostream>
using namespace std;
class A {
    public:
    virtual void print() {
        cout << "class A\n";
    }
};

class B : public A {
    private:
    void print() override {
        cout << "class B\n";
    }
};

int main() {
    B b;
    // b.print();

    A* a = &b;
    a->print();
}