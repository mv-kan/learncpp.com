#include <iostream>

class FixedPoint2
{
    void parseTwoInt(int16_t base, int16_t decimal)
    {
        mBase = base;
        mDecimal = decimal;
        if (mBase < 0 || mDecimal < 0)
        {
            mBase = -static_cast<int16_t>(std::abs(mBase));
            mDecimal = static_cast<int16_t>(std::abs(mDecimal));
        }
    }

public:
    FixedPoint2(int16_t base, int16_t decimal) : mBase{base}, mDecimal{decimal}
    {
        if (mBase < 0 || mDecimal < 0)
        {
            mBase = -static_cast<int16_t>(std::abs(mBase));
            mDecimal = static_cast<int16_t>(std::abs(mDecimal));
        }
    }

    FixedPoint2(double num)
    {
        int16_t base = static_cast<int16_t>(num);
        int16_t decimal = static_cast<int16_t>(num * 100) % 100;
        parseTwoInt(base, decimal);
    }

    operator double() const
    {
        double result{std::abs((double)mBase) + static_cast<double>(mDecimal) / 100};
        return mBase < 0 ? -result : result;
    }

private:
    int16_t mBase{};
    int16_t mDecimal{};
};
std::ostream &operator<<(std::ostream &out, const FixedPoint2 &p)
{
    out << double(p);
    return out;
}

int main()
{
    // Handle cases where the argument is representable directly
    FixedPoint2 a{0.01};
    std::cout << a << '\n';

    FixedPoint2 b{-0.01};
    std::cout << b << '\n';

    // Handle cases where the argument has some rounding error
    FixedPoint2 c{5.01}; // stored as 5.0099999... so we'll need to round this
    std::cout << c << '\n';

    FixedPoint2 d{-5.01}; // stored as -5.0099999... so we'll need to round this
    std::cout << d << '\n';

    // Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
    FixedPoint2 e{106.9978}; // should be stored with base 107 and decimal 0
    std::cout << e << '\n';

    FixedPoint2 f{1.9}; // make sure we handle single digit decimal
    std::cout << f;

    return 0;
}