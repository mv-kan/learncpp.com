#include <iostream>

class MyString
{
    std::string mStr;

public:
    MyString(std::string s): mStr{s} {
    }
    std::string operator()(size_t i, size_t c) { 
        return mStr.substr(i, c); 
    }
};

int main()
{
    using std::cout;

    MyString s{"Hello, world!"};
    cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

    return 0;
}