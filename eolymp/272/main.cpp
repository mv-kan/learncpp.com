#include <cstring>
#include <stdio.h>
#include "huge.h"

#define HUGE_CAPACITY 5000
#define MAX_CHAR_INPUT 30000

class NumConverter
{
    static char ToChar(const UIntInternal decimal)
    {
        if (decimal <= 9)
            return decimal + '0';
        assert(false && "shouldn't be here");
        return 0;
    }

    static UIntInternal ToDecimal(const char digit)
    {
        if (digit >= 48 && digit <= 57)
            return digit - '0';
        assert(false && "shouldn't be here");
        return 0;
    }
    static size_t GetLastDigit(const char *str)
    {
        size_t nullchar{};

        while (str[nullchar] != '\0')
        {
            nullchar++;
        }
        // go back and search
        for (size_t i = 0; i < nullchar; i++)
        {
            char digit{str[nullchar - i - 1]};

            if ((digit >= '0' && digit <= '9') || (digit >= 'A' && digit <= 'Z'))
            {
                return nullchar - i - 1;
            }
        }
        assert(false && "Shouldn't be here");
        return 0;
    }

public:
    static Huge ParseStr(const char *str)
    {
        size_t len = GetLastDigit(str) + 1;

        Huge result{0, HUGE_CAPACITY};
        UIntInternal numDigit{1};
        UIntInternal tmpChunk{};
        size_t chunkindex{};
        for (size_t i = 0; i < len; i++)
        {
            UIntInternal n{ToDecimal(str[len - 1 - i])};
            tmpChunk = (n * numDigit) + tmpChunk;

            numDigit *= 10; // base 10
            if (numDigit >= hugeBase)
            {
                numDigit = 1;
                result.SetAt(chunkindex, tmpChunk);
                tmpChunk = 0;
                chunkindex++;
            }
        }
        // last iteration
        if (tmpChunk)
        {
            result.SetAt(chunkindex, tmpChunk);
        }
        return result;
    }
    static void PrintHuge(const Huge &huge)
    {
        char buf[MAX_CHAR_INPUT];
        size_t bufSize{};
        size_t len{huge.GetLen()};
        for (size_t i = 0; i < len; i++)
        {
            for (UIntInternal n = 10; n <= hugeBase; n *= 10)
            {
                // scrap digit from n
                UIntInternal digit = huge.GetAt(i) % n / (n / 10);
                buf[bufSize] = ToChar(digit);
                bufSize++;
            }
        }
        // trim from zeros in the end
        while (bufSize > 1)
        {
            if (buf[bufSize - 1] == '0')
                bufSize--;
            else
                break;
        }

        for (size_t i = 0; i < bufSize; i++)
        {
            printf("%c", buf[bufSize - 1 - i]);
        }
        printf("\n");
    }
};

int main()
{
    char buf[MAX_CHAR_INPUT];
    // scanf auto add \0 at the end of buf
    scanf("%s", buf);

    Huge a = NumConverter::ParseStr(buf);

    scanf("%s", buf);
    Huge b = NumConverter::ParseStr(buf);


    a.Multiply(b);
    // HugeView av{&a, 0, 1};

    // for (size_t i = av.GetBegin(); i < av.GetEnd() + 1; i++)
    // {
    //     printf(" %zu ", av.GetAt(i));
    // }
    // printf("\n");
    // a.Print();
    NumConverter::PrintHuge(a);
}