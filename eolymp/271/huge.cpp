#include "huge.h"
#include <stdio.h>
#include <limits>
#include <utility>

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

void Huge::Set(size_t value)
{
    std::size_t len{0};
    do
    {
        mChunks[len] = value % hugeBase;
        ++len;
        value /= hugeBase;
    } while (value);

    mLen = len;
    assert(mLen <= mCapacity);
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
    if (mChunks)
        delete[] mChunks;
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

void Huge::Subtract(const Huge &huge)
{
    AssertThis();
    huge.AssertThis();
    assert(huge.mCapacity == mCapacity);
    assert(huge.mLen <= mLen);

    UIntInternal borrow = 0;
    for (size_t i = 0; i < huge.mLen || borrow != 0; i++)
    {
        // we need to know when subtract is negative
        int64_t subtract = (int64_t)mChunks[i] - (int64_t)borrow;
        if (i < huge.mLen)
            subtract -= huge.mChunks[i];

        borrow = subtract < 0 ? 1 : 0;

        // borrowed things, here we might have conversion error
        UIntInternal borrowed = hugeBase * borrow;

        // this is subtraction or addition depending on sign of subtract
        borrowed += subtract;

        // assign subtraction of borrowed to result
        mChunks[i] = borrowed;
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

// actually this rotates it to right, but left rotation usually is something that result in bigger number
void Huge::ChunkShiftLeft()
{
    AssertThis();
    assert(mLen + 1 < mCapacity);
    memmove(mChunks + 1, mChunks, sizeof(UIntInternal) * (mLen - 1));
    mLen++;
    mChunks[0] = 0;
}
// actually this rotates it to the left, but left rotation usually is something that result in bigger number
void Huge::ChunkShiftRight()
{
    AssertThis();
    memmove(mChunks, mChunks + 1, sizeof(UIntInternal) * (mLen - 1));
    mChunks[mLen - 1] = 0;
    if (mLen > 1)
        mLen--;
}

void Huge::Reduce() {
    for (size_t i = 0; i < mLen; i++)
    {
        size_t irev{ mLen - i - 1 };
        if (mChunks[irev] != 0) {
            mLen = irev + 1;
            return;
        }
    }
    // for 0 len is 1
    mLen = 1;
}

void Huge::Multiply(const Huge &huge)
{
    /*
    1234 a [3..0]
     567 b [2..0]
    // r is num digit for result with remainder
    r[0] = a[0] * b[0]
    r[1] = a[0] * b[1] + b[0] * a[1]
    r[2] = a[0] * b[2] + a[1] * b[1] + a[2] * b[0]
    r[3] = a[0] * b[3] + a[1] * b[2] + a[2] * b[1] + a[3] * b[0]
    r[4] = a[0] * b[4] + a[1] * b[3] + a[2] * b[2] + a[3] * b[1] + a[4] * b[0]
    */
    Huge result{0, mCapacity};
    // each time we increment mLen of result, so to avoid 
    // creating logic for first mLen increment I just decrement mLen before the loop
    result.mLen--;

    size_t i{};
    // remainder 
    UIntInternal r{};
    do
    {
        for (size_t j = 0; j <= i; j++) {
            // this means that j is out of bounds of mChunks
            // and out of bound value is zero in this context 
            // and if we multiply zero on anything we get zero, so we can skip this iteration if we got one
            if (j >= mLen)
                continue;
            if (i - j >= huge.mLen)
                continue;

            r += mChunks[j] * huge.mChunks[i - j];
        }
        result.mChunks[i] = r % hugeBase;
        result.mLen++;
        r = r / hugeBase;
        i++;
    } while (i < mLen * 2 || i < huge.mLen * 2);

    result.Reduce();
    *this = std::move(result);
}

// if base is too big then calculation may overflow internal variable, leading to wrong results
void Huge::Multiply(const UIntInternal num)
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
