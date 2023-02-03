#include <iostream>

#include <exception>

class Fraction
{
public:
    Fraction(int num, int denom): _num{num}, _denom{denom} {
        if (_denom == 0) {
            throw std::runtime_error{"Invalid denominator"};
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f){
        out << f._num << "/" << f._denom;
        return out;
    }
private:
    int _num{};
    int _denom{};
};

int main()
{
    using std::cout, std::cin;

    int num{}, denom{};

    cout << "Enter the numerator: ";
    cin >> num;

    cout << "Enter the denominator: ";
    cin >> denom;
    try {
        Fraction f{num, denom};
        cout << f << std::endl;
    } 
    catch (const std::exception& e) {
        cout << e.what() << std::endl;
    }
    return 0;
}