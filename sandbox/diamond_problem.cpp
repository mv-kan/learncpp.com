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



class B : virtual public A
{
private:
    /* data */
public:
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


class C: virtual public A
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

class D: public B, public C
{
private:
    /* data */
public:
    D(/* args */);
    ~D();
};

D::D(/* args */)
{
    cout << "D()" << endl;
}

D::~D()
{
    cout << "~D()" << endl;

}

int main() {
    D d;
    // cout << d.B::x << endl;
    // cout << d.C::x << endl;
    cout << d.x << endl;
}