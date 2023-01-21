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

void Huge::Add(const Huge &huge)
{
    assert(mCapacity == huge.mCapacity && "in this program capacity between Huge objects HAVE TO be the same");
    AssertThis();
    huge.AssertThis();

    // if our object has less lenght than huge then we...
    if (mLen < huge.mLen)
    {
        // ...extent *this and fill it with zeros
        for (std::size_t i = mLen; i < huge.mLen; i++)
        {
            mChunks[i] = 0;
        }
        // we adding so *this object is going to have huge lenght (if it is bigger)
        mLen = huge.mLen;
    }
    UIntInternal remainder{0};
    for (std::size_t i = 0; i < mLen; i++)
    {
        // mLen always bigger or equal to huge.mLen
        UIntInternal hugeValue{(i < huge.mLen) ? huge.mChunks[i] : static_cast<UIntInternal>(0)};

        // sum of remainder, huge value and *this
        UIntInternal sum = mChunks[i] + hugeValue + remainder;

        mChunks[i] = sum % hugeBase;
        remainder = sum / hugeBase;

        // if no remainder left and huge.mLen is already walked thru then we calculated addition
        // we can return here
        if (!remainder && i >= huge.mLen)
            return;
    }

    if (remainder)
    {
        assert(mLen + 1 < mCapacity && "Overflow, resize is not implemented");

        mChunks[mLen] = remainder;
        mLen++;
    }
}

// if base is too big then calculation may overflow internal variable, leading to wrong results
void Huge::Multiply(UIntInternal num)
{
    AssertThis();

    UIntInternal carry{0};

    for (size_t i = 0; i < mLen; i++)
    {
        size_t multiplied = static_cast<size_t>(mChunks[i]) * num + carry;

        mChunks[i] = multiplied % hugeBase;
        carry = multiplied / hugeBase;
    }

    // num * mChunks[i] cannot overflow carry to the point we need to do iteration
    if (carry > 0)
    {
        assert(mLen != mCapacity && "overflow will occur!!!");

        mChunks[mLen] = carry;
        mLen++;
    }
}

void Huge::Divide(UIntInternal num)
{
    AssertThis();

    UIntInternal borrow{0};

    for (size_t i = 0; i < mLen; i++)
    {
        // reversed index
        size_t index{mLen - i - 1};

        // with cusve braces init compiler throws a lot of warnings
        UIntInternal sum = borrow + mChunks[index];

        UIntInternal division = sum / num;
        UIntInternal remainder = sum % num;

        mChunks[index] = division;

        borrow = remainder * hugeBase;
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

UIntInternal Huge::CalcModule(UIntInternal num) const
{
    AssertThis();

    UIntInternal borrow{};
    UIntInternal remainder{};
    for (size_t i = 0; i < mLen; i++)
    {
        // reversed index
        size_t index{mLen - i - 1};

        // with cusve braces init compiler throws a lot of warnings
        UIntInternal sum = borrow + mChunks[index];

        remainder = sum % num;

        borrow = remainder * hugeBase;
    }
    return remainder;
}