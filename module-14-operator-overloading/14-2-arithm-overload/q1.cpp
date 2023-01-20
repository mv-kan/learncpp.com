#include <iostream>

class Fraction
{
    int m_num = 0;
    int m_denum = 1;

public:
    Fraction(int num = 0, int denum = 1) : m_num{num}, m_denum{denum}
    {}

    void print() {
        printf("%d/%d\n", m_num, m_denum);
    }

	friend Fraction operator*(const Fraction, const Fraction);

    // friend Fraction operator*(const Fraction, const int);
    // friend Fraction operator*( const int, const Fraction);
};

Fraction operator*(const Fraction a, const Fraction b) {
    return Fraction{a.m_num * b.m_num, a.m_denum * b.m_denum};
}

// Fraction operator*(const Fraction f, const int n) {
//     return Fraction{f.m_num * n, f.m_denum};
// }

// Fraction operator*(const int n, const Fraction f) {
//     return f * n;
// }

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    return 0;
}