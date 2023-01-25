#include "huge_view.h"

void HugeView::AssertThis(){
    assert(mHuge != nullptr);
}

HugeView::HugeView(const Huge *huge, size_t begin, intmax_t end) : mHuge{huge}, mBegin{begin}
{
    assert(static_cast<intmax_t>(begin) <= end || end == -1);
    mEnd = end == -1 ? huge->GetLen() - 1 : end;
    assert(huge->GetLen() > mEnd);
}

UIntInternal HugeView::GetAt(size_t index)
{
    AssertThis();
    // this is not proper error handling but for eolymp task it is good enough
    assert(mHuge->GetLen() > index);
    assert(index >= mBegin);
    assert(index <= mEnd);

    return mHuge->GetAt(index);
}

void HugeView::SplitAt(HugeView *a, HugeView *b, size_t at) const {
    AssertThis();
    // set to mHuge
    a->mHuge = mHuge;
    b->mHuge = mHuge;

    // a is going to have splice from mBegin -> mBegin + at
    a->mBegin = mBegin;
    a->mEnd = mBegin + at - 1;

    // b is going to have splice from mBegin -> mBegin + at
    b->mBegin = mBegin + at;
    b->mEnd = mEnd;
}