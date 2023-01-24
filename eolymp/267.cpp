#include <cstring>
#include <stdio.h>
#if !defined(HUGE_H)
#define HUGE_H

/*
Chunk means just one of whole thing, so Chunks just the whole huge number we store

Invariants

1. Huge::len is minimal required numbers of chunks for storing a number, other things in capacity is garbage
2. Huge::len minimal value is 1, if 0 then invalid object

Implementation suggestions

1. create add from add_assign and etc etc

Name conventions

class = PascalCase
variables = camelCase
function = PascalCase
*/

#include <cstdint>
#include <cassert>
#include <stddef.h>
// base of each UIntInternal chunk
#define UINT_INTERNAL_BASE 1000000000
// #define UINT_INTERNAL_BASE 10

using UIntInternal = std::uint64_t;

// internal linkage by default
// base of Huge class
// Base here means what is the max value we can store in one chunk
constexpr UIntInternal hugeBase{UINT_INTERNAL_BASE};

class Huge
{
    std::size_t mLen{0};
    std::size_t mCapacity{0};
    UIntInternal *mChunks{nullptr};
    // set len to 1 and value of first chunk to 0
    void BasicAllocation(const std::size_t capacity);

    // assert itself, i.e. if any of methods are called *this has to be not empty
    void AssertThis() const;

public:
    // rule of 3
    // constructor
    // copy constructor
    // assign constructor
    // destructor

    Huge(std::size_t value, const std::size_t capacity);

    Huge(const Huge &huge);

    Huge &operator=(const Huge &huge);

    ~Huge();

    // move constructor and move assignment

    Huge(Huge &&source);

    Huge &operator=(Huge &&source);

    // prints in reverse, least significant bit in left
    void Print() const;

    // math operations
    bool IsZero() const;

    // returns -1 if this is bigger
    // returns 0 if equal
    // returns 1 if huge is bigger
    int Compare(const Huge &huge) const;
    // get chunk at index
    UIntInternal GetAt(size_t i) const;

    // set chunk at index
    void SetAt(size_t i, UIntInternal value);

    size_t GetLen() const { return mLen; }

    void Subtract(const Huge &huge);
};

#endif // HUGE_H
#include <stdio.h>
// I cannot see where it was raised, but debugger will save the day
void Huge::AssertThis() const
{
    assert(mChunks && "to perform task need mChunks not nullptr");
    assert(mCapacity > 0 && "mCapacity is 0, to perform task need mCapacity bigger than 0");
    assert(mLen > 0 && "mLen is 0, to perform task need mLen bigger than 0, because mLen 0 is invalid value");
}

void Huge::BasicAllocation(const std::size_t capacity)
{
    assert(capacity > 0 && "capacity cannot be 0");

    mCapacity = capacity;
    mChunks = new UIntInternal[mCapacity];
    mLen = 1;
    mChunks[0] = 0;
}

Huge::Huge(std::size_t value, const std::size_t capacity)
{
    BasicAllocation(capacity);

    std::size_t len{0};
    do
    {
        mChunks[len] = value % hugeBase;
        ++len;
        value /= hugeBase;
    } while (value);

    mLen = len;
}

Huge::~Huge()
{
    // no assert because we implemented move constructor
    // assert(mChunks && "mChunks has to be freed by Huge destructor");
    if (mChunks)
    {
        delete[] mChunks;
    }
    mLen = 0;
    mCapacity = 0;
}

Huge::Huge(const Huge &huge)
{
    BasicAllocation(huge.mCapacity);
    huge.AssertThis();

    for (std::size_t i = 0; i < huge.mLen; i++)
    {
        mChunks[i] = huge.mChunks[i];
    }
    mLen = huge.mLen;
}

Huge &Huge::operator=(const Huge &huge)
{
    huge.AssertThis();
    assert(mCapacity == huge.mCapacity && "in this program capacity between Huge objects HAVE TO be the same");

    for (std::size_t i = 0; i < huge.mLen; i++)
    {
        mChunks[i] = huge.mChunks[i];
    }
    mLen = huge.mLen;
    return *this;
}

// move constructor
// QUESTION why double reference?
Huge::Huge(Huge &&source)
{
    assert(source.mCapacity > 0);

    mChunks = source.mChunks;
    mLen = source.mLen;
    mCapacity = source.mCapacity;

    source.mChunks = nullptr;
    source.mLen = 0;
    source.mCapacity = 0;
}

// move assignment
Huge &Huge::operator=(Huge &&source)
{
    assert(source.mCapacity > 0);

    mChunks = source.mChunks;
    mLen = source.mLen;
    mCapacity = source.mCapacity;

    source.mChunks = nullptr;
    source.mLen = 0;
    source.mCapacity = 0;

    return *this;
}

// math operations
bool Huge::IsZero() const
{
    AssertThis();

    return (mLen == 1 && mChunks[0] == 0);
}

void Huge::Print() const
{
    AssertThis();
    for (size_t i = 0; i < mLen; i++)
    {
        printf(" %zu ", mChunks[i]);
    }
}

int Huge::Compare(const Huge &huge) const
{
    if (mLen != huge.mLen)
        return mLen > huge.mLen ? -1 : 1;

    for (size_t i = 0; i < mLen; i++)
    {
        // in reverse because the latest chunk is the biggest
        size_t irev = mLen - 1 - i;
        // *this is bigger
        if (mChunks[irev] > huge.mChunks[irev])
            return -1;
        // huge is bigger
        else if (mChunks[irev] < huge.mChunks[irev])
            return 1;
    }
    // equal
    return 0;
}

// get chunk at index
UIntInternal Huge::GetAt(size_t i) const
{
    assert(i < mLen);

    return mChunks[i];
}

// set chunk at index
// doesn't handle all edge case, so sometimes this methods doesn't work properly
// because of invariant of every huge has to be minimal required len
void Huge::SetAt(size_t i, UIntInternal value)
{
    assert(i < mCapacity);
    if (i >= mLen)
        mLen = i + 1;
    mChunks[i] = value;
}

void Huge::Subtract(const Huge &huge)
{
    AssertThis();
    huge.AssertThis();
    assert(huge.mCapacity == mCapacity);
    assert(huge.mLen <= mLen);

    UIntInternal borrow = 0;
    for (size_t i = 0; i < huge.mLen; i++)
    {
        // we need to know when subtract is negative
        int64_t subtract = ((int64_t)mChunks[i] - (int64_t)borrow) - (int64_t)huge.mChunks[i];
        if (subtract < 0)
        {
            // yes borrow here
            borrow = 1;
            // borrowed things, here we might have conversion error
            // but you just gotta disable it, because here it was explicit type conversion
            UIntInternal borrowed = ~(UIntInternal)0 % hugeBase;
            // this is actually subtraction
            borrowed += (UIntInternal)subtract;
            // assign subtraction of borrowed to result
            mChunks[i] = borrowed;
        }
        else
        {
            // no borrow here
            borrow = 0;

            mChunks[i] = subtract;
        }
    }
    // keep len to its required minimum
    UIntInternal actualLen{};
    for (size_t i = 0; i < mLen; i++)
    {
        if (mChunks[mLen - i - 1] != 0)
        {
            actualLen = mLen - i;
            break;
        }
    }
    // if zero then keep len to 1
    mLen = actualLen ? actualLen : 1;
}
#define HUGE_CAPACITY 100000
#define MAX_CHAR_INPUT 15000

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
        size_t len{huge.GetLen()};
        for (size_t i = 0; i < len; i++)
        {
            size_t irev{len - 1 - i};
            printf("%zu", huge.GetAt(irev));
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

    a.Subtract(b);

    NumConverter::PrintHuge(a);
}