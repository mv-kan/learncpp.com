#include "huge_view.h"
HugeView::HugeView(const Huge *huge, size_t begin, intmax_t end) : mHuge{huge}, mBegin{begin}
{
    assert(static_cast<intmax_t>(begin) <= end || end == -1);
    mEnd = end == -1 ? huge->GetLen() - 1 : end;
    assert(huge->GetLen() > mEnd);
}

UIntInternal HugeView::GetAt(size_t index)
{
    // this is not proper error handling but for eolymp task it is good enough
    assert(mHuge->GetLen() > index);
    assert(index >= mBegin);
    assert(index <= mEnd);

    return mHuge->GetAt(index);
}
