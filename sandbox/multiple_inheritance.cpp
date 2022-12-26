#include<iostream>

using namespace std;

class A
{
private:
    /* data */
public:
    int x = 10;
    A(/* args */);
    ~A();
};

A::A(/* args */)
{
    cout << "A()" << endl;
}

A::~A()
{
    cout << "~A()" << endl;

}


class B
{
private:
    /* data */
public:
    int x = 5;
    B(/* args */);
    ~B();
};

B::B(/* args */)
{
    cout << "B()" << endl;
}

B::~B()
{
    cout << "~B()" << endl;

}

class C: public A, public B
{
private:
    /* data */
public:
    C(/* args */);
    ~C();
};

C::C(/* args */)
{
    cout << "C()" << endl;
}

C::~C()
{
    cout << "~C()" << endl;

}

int main() {
    C c;
    cout << c.A::x << endl;
    cout << c.B::x << endl;
}