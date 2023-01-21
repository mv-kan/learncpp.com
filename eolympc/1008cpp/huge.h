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
#include <string>
// base of each UIntInternal chunk
#define UINT_INTERNAL_BASE 100

using UIntInternal = std::uint16_t;

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

    void Add(const Huge &huge);

    void Multiply(UIntInternal num);

    void Divide(UIntInternal num);

    UIntInternal CalcModule(UIntInternal num) const;
};

#endif // HUGE_H
