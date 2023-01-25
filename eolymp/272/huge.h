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
#include <string.h>
#include <stddef.h>
// base of each UIntInternal chunk
// #define UINT_INTERNAL_BASE 1000000000 // UINT_INTERNAL_BASE * UINT_INTERNAL_BASE mustn't overflow 64 bits
#define UINT_INTERNAL_BASE 10

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

    // for multiplying
    void ChunkShiftLeft();

    void ChunkShiftRight();

    Huge Karatsuba(const Huge& a, const Huge& b);

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

    // set chunk at index, not safe function
    void SetAt(size_t i, UIntInternal value);

    size_t GetLen() const { return mLen; }

    // math
    void Subtract(const Huge &huge);

    void Add(const Huge &huge);

    void Multiply(const Huge& huge);

};

#endif // HUGE_H
