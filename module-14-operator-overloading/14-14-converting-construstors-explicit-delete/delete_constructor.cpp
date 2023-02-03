#include <string>
#include <iostream>

class MyString
{
private:
    std::string m_string;

public:
    MyString(char) = delete; // any use of this constructor is an error

    // explicit keyword makes this constructor ineligible for implicit conversions
    explicit MyString(int x) // allocate string of size x /
    {
        m_string.resize(x);
    }

    MyString(const char *string) // allocate string to hold string value
    {
        m_string = string;
    }

    friend std::ostream &operator<<(std::ostream &out, const MyString &s);
};

std::ostream &operator<<(std::ostream &out, const MyString &s)
{
    out << s.m_string;
    return out;
}

int main()
{
    MyString mine('x'); // compile error, since MyString(char) is deleted
    std::cout << mine;
    return 0;
}