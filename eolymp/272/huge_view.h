#if !defined(HUGE_VIEW_H)
#define HUGE_VIEW_H
#include <cstdint>
#include "huge.h"

// forward declare Huge to work

// HugeView is class that doesn't allocate anything, but can split up mChunks into small chunks
class HugeView
{
private:
    const Huge *mHuge = nullptr;
    // begin is index of mChunks
    size_t mBegin = 0;
    size_t mEnd = 0;

public:
    // if end equal to 0 , if end == -1 then end is equal to huge->GetLen()
    HugeView(const Huge* huge, size_t begin = 0, intmax_t end = -1);
    // get mChunk value
    UIntInternal GetAt(size_t index);

    size_t GetBegin() { return mBegin; }
    // this is index, not size!!!
    size_t GetEnd() { return mEnd; }
};

#endif // HUGE_VIEW_H
