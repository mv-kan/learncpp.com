#if !defined(HUGE_VIEW_H)
#define HUGE_VIEW_H
#include <cstdint>
#include "huge.h"

// forward declare Huge to work
class Huge;
// HugeView is class that doesn't allocate anything, but can split up mChunks into small chunks
class HugeView
{
private:
    const Huge *mHuge = nullptr;
    // begin is index of mChunks
    size_t mBegin = 0;
    size_t mEnd = 0;
    void AssertThis();
public:
    HugeView() = default;

    // if end equal to 0 , if end == -1 then end is equal to huge->GetLen()
    HugeView(const Huge* huge, size_t begin = 0, intmax_t end = -1);
    // get mChunk value
    UIntInternal GetAt(size_t index);

    size_t GetBegin() { return mBegin; }
    // this is index, not size!!!
    size_t GetEnd() { return mEnd; }

    size_t GetLen() {return mEnd - mBegin + 1;}
    // @at this is parameter that calculates from begin like begin + at, at this point we split
    // so this is not absolute value, this is relative begin 
    void SplitAt(HugeView*a, HugeView*b, size_t at) const;
};

#endif // HUGE_VIEW_H
