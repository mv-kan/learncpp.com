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

// base of each UIntInternal chunk
#define UINT_INTERNAL_BASE 100

using UIntInternal = std::uint16_t;

// internal linkage by default
// base of Huge class
// Base here means what is the max value we can store in one chunk 
constexpr UIntInternal hugeBase{UINT_INTERNAL_BASE};

class Huge
{
    size_t mLen{0};
    size_t mCapacity{0};
    UIntInternal *mChunks{nullptr};
    // set len to 1 and value of first chunk to 0
    void BasicAllocation(const size_t capacity);
public:
    // rule of 3
    // constructor
    // copy constructor
    // assign constructor
    // destructor

    Huge(size_t value, const size_t capacity);

    Huge(const Huge& huge);
    
    Huge& operator=(const Huge& huge);

    ~Huge();
    
    // move constructor
    

    // math operations
    bool IsZero();

    void Add(const Huge& huge); 

    void Multiply(UIntInternal num);

    void Divide(UIntInternal num); 

    UIntInternal CalcModule(UIntInternal num);
}

#endif // HUGE_H
