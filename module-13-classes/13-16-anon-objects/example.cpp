#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents)
        : m_cents { cents }
    {}

    int getCents() const { return m_cents; }
};

Cents add(const Cents& c1, const Cents& c2)
{
    // List initialization looks at the return type of the function
    // and creates the correct object accordingly.
    return { c1.getCents() + c2.getCents() }; // return anonymous Cents value
}

int main()
{
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    std::cout << "I have " << add(cents1, cents2).getCents() << " cents.\n"; // print anonymous Cents value

    return 0;
}