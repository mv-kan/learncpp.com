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

    friend std::ostream& operator<< (std::ostream& out, const Fraction& frac);
    friend std::istream& operator>> (std::istream& in, Fraction& frac);
};

Fraction operator*(const Fraction a, const Fraction b) {
    return Fraction{a.m_num * b.m_num, a.m_denum * b.m_denum};
}

std::ostream& operator<< (std::ostream& out, const Fraction& frac) {
    out << frac.m_num;
    out << "/";
    out << frac.m_denum;
    return out;
}

std::istream& operator>> (std::istream& in, Fraction& frac) {
    in >> frac.m_num;
    in >> frac.m_denum;
    return in;
}


int main()
{
	Fraction f1;
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;

	Fraction f2;
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;

	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // note: The result of f1 * f2 is an r-value

	return 0;
}