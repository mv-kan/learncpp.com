#include<iostream>

using namespace std;

class Base
{
private:
    /* data */
public:
    Base() {
        cout << "Base()" << endl;
    }
    ~Base() {
        cout << "~Base()" << endl;
    }
    void Info() {
        cout << "Base::Info()" << endl;
    }
};

class Child: public Base
{
private:
    /* data */
public:
    Child() {
        cout << "Child()" << endl;
    }
    ~Child() {
        cout << "~Child()" << endl;
    }
    void Info() {
        cout << "Child::Info()" << endl;
    }
};

int main() {
    Base* baseptr;
    Child child; 

    baseptr = &child;

    child.Info();
    baseptr->Info();

    Base& baseref{child};

    baseref.Info();
}