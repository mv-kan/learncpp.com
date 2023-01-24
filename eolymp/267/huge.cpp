#include "huge.h"
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