#include <iostream>
#include <cstring>

#include "huge.h"

#define HUGE_CAPACITY 1000
#define MAX_CHAR_INPUT 1000

// Can convert from 2 base to 36 base and everything in between
class NumberConverter
{
    static char ToChar(const UIntInternal decimal)
    {
        if (decimal <= 9)
            return decimal + '0';
        else
            return decimal + 'A' - 10; 
    }

    static UIntInternal ToDecimal(const char digit)
    {
        if (digit >= 48 && digit <= 57) 
            return digit - '0';
        else 
            return digit - 'A' + 10;
    }

    static void MultiplyInto(Huge &dest, const Huge &a, const UIntInternal b) {
        // copy assignment 
        dest = a;
        dest.Multiply(b);
    }
public:
    static Huge ParseStr(const std::string& str, const UIntInternal base)
    {
        size_t len = str.length();
    
        Huge result{0, HUGE_CAPACITY};
        Huge tmp{0, HUGE_CAPACITY};
        Huge numDigit{1, HUGE_CAPACITY}; // numerical digit
        
        for (size_t i = 0; i < len; i++)
        {
            UIntInternal decimal{ToDecimal(str[len - i - 1])};

            MultiplyInto(tmp, numDigit, decimal);
            result.Add(tmp);
            numDigit.Multiply(base);
        }
        
        return result;
    }

    static std::string ToStr()
    {
        return "";
    }
};

int main()
{
    std::string input{};

    std::getline(std::cin, input);
    std::cout << input << std::endl;
    auto num = NumberConverter::ParseStr(input, 10);
    num.Print();
}