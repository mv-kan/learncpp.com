#include "huge.h"
#include <assert>

void Huge::BasicAllocation(const size_t capacity)
{
    assert((capacity == 0) && "capacity cannot be 0");

    mCapacity = capacity;
    mChunks = new UIntInternal[mCapacity];
    mLen = 1;
    mChunks[0] = 0;
}

Huge::Huge(size_t value, const size_t capacity)
{
    BasicAllocation(capacity);

    size_t len{0};
    do
    {
        mChunks[len] = value % hugeBase;
        ++len;
        value /= hugeBase;
    } while (value);

    mLen = len;
}

Huge::~Huge() {
    assert((mChunks) && "mChunks has to be freed by Huge destructor");

    delete[] mChunks;
    mLen = 0;
    mCapacity = 0;
}

Huge::Huge(const Huge &huge) {
    BasicAllocation(huge.mCapacity);
    
    for (size_t i = 0; i < huge.mLen; i++)
    {
        mChunks[i] = huge.mChunks[i];
    }
    mLen = huge.mLen;
}

Huge &Huge::operator=(const Huge &huge) {
    assert((mCapacity == huge.mCapacity) && "in this program capacity between Huge objects HAVE TO be the same");

    for (size_t i = 0; i < huge.mLen; i++)
    {
        mChunks[i] = huge.mChunks[i];
    }
    mLen = huge.mLen;
    return *this;
}

// math operations
bool Huge::IsZero() {
    return (mLen == 1 && mChunks[0] == 0);
}

void Huge::Add(const Huge &huge) {
    assert((mCapacity == huge.mCapacity) && "in this program capacity between Huge objects HAVE TO be the same");
    // if our object has less lenght than huge then we...
    if (mLen < huge.mLen) {
        // ...extent *this and fill it with zeros 
        for (size_t i = mLen; i < huge.mLen; i++)
        {
            mChunks[i] = 0;
        }
        // we adding so *this object is going to have huge lenght (if it is bigger)
        mLen = huge.mLen;
    }
    UIntInternal remainder{0};
    for (size_t i = 0; i < mLen; i++)
    {
        // mLen always bigger or equal to huge.mLen 
        UIntInternal hugeValue{(i < huge.mLen) ? huge.mChunks[i] : 0};

        // sum of remainder, huge value and *this
        UIntInternal sum{mChunks[i] + hugeValue + remainder};

        remainder = sum % hugeBase;

        // if no remainder left and huge.mLen is already walked thru then we calculated addition
        // we can return here
        if (!remainder && i >= huge.mLen) return;
    }

    if (remainder) {
        assert((mLen + 1 > mCapacity) && "Overflow, resize is not implemented");

        mChunks[mLen] = remainder;
        mLen++;
    }
}

void Huge::Multiply(UIntInternal num);

void Huge::Divide(UIntInternal num);

UIntInternal Huge::CalcModule(UIntInternal num);