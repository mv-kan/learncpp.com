// #include <iostream>
// #include <cstring>
// #if !defined(HUGE_H)
// #define HUGE_H

// /*
// Chunk means just one of whole thing, so Chunks just the whole huge number we store

// Invariants

// 1. Huge::len is minimal required numbers of chunks for storing a number, other things in capacity is garbage
// 2. Huge::len minimal value is 1, if 0 then invalid object

// Implementation suggestions

// 1. create add from add_assign and etc etc

// Name conventions

// class = PascalCase
// variables = camelCase
// function = PascalCase
// */

// #include <cstdint>
// #include <cassert>
// #include <string>
// // base of each UIntInternal chunk
// #define UINT_INTERNAL_BASE 1000000000

// using UIntInternal = std::uint64_t;

// // internal linkage by default
// // base of Huge class
// // Base here means what is the max value we can store in one chunk
// constexpr UIntInternal hugeBase{UINT_INTERNAL_BASE};

// class Huge
// {
//     std::size_t mLen{0};
//     std::size_t mCapacity{0};
//     UIntInternal *mChunks{nullptr};
//     // set len to 1 and value of first chunk to 0
//     void BasicAllocation(const std::size_t capacity);

//     // assert itself, i.e. if any of methods are called *this has to be not empty
//     void AssertThis() const;

// public:
//     // rule of 3
//     // constructor
//     // copy constructor
//     // assign constructor
//     // destructor

//     Huge(std::size_t value, const std::size_t capacity);

//     Huge(const Huge &huge);

//     Huge &operator=(const Huge &huge);

//     ~Huge();

//     // move constructor and move assignment

//     Huge(Huge &&source);

//     Huge &operator=(Huge &&source);

//     // prints in reverse, least significant bit in left
//     void Print() const;

//     // math operations
//     bool IsZero() const;

//     void Add(const Huge &huge);

//     void Multiply(UIntInternal num);

//     void Divide(UIntInternal num);

//     UIntInternal CalcModule(UIntInternal num) const;
// };

// #endif // HUGE_H

// #include <iostream>
// // I cannot see where it was raised, but debugger will save the day
// void Huge::AssertThis() const
// {
//     assert(mChunks && "to perform task need mChunks not nullptr");
//     assert(mCapacity > 0 && "mCapacity is 0, to perform task need mCapacity bigger than 0");
//     assert(mLen > 0 && "mLen is 0, to perform task need mLen bigger than 0, because mLen 0 is invalid value");
// }

// void Huge::BasicAllocation(const std::size_t capacity)
// {
//     assert(capacity > 0 && "capacity cannot be 0");

//     mCapacity = capacity;
//     mChunks = new UIntInternal[mCapacity];
//     mLen = 1;
//     mChunks[0] = 0;
// }

// Huge::Huge(std::size_t value, const std::size_t capacity)
// {
//     BasicAllocation(capacity);

//     std::size_t len{0};
//     do
//     {
//         mChunks[len] = value % hugeBase;
//         ++len;
//         value /= hugeBase;
//     } while (value);

//     mLen = len;
// }

// Huge::~Huge()
// {
//     // no assert because we implemented move constructor
//     // assert(mChunks && "mChunks has to be freed by Huge destructor");
//     if (mChunks)
//     {
//         delete[] mChunks;
//     }
//     mLen = 0;
//     mCapacity = 0;
// }

// Huge::Huge(const Huge &huge)
// {
//     BasicAllocation(huge.mCapacity);
//     huge.AssertThis();

//     for (std::size_t i = 0; i < huge.mLen; i++)
//     {
//         mChunks[i] = huge.mChunks[i];
//     }
//     mLen = huge.mLen;
// }

// Huge &Huge::operator=(const Huge &huge)
// {
//     huge.AssertThis();
//     assert(mCapacity == huge.mCapacity && "in this program capacity between Huge objects HAVE TO be the same");

//     for (std::size_t i = 0; i < huge.mLen; i++)
//     {
//         mChunks[i] = huge.mChunks[i];
//     }
//     mLen = huge.mLen;
//     return *this;
// }

// // move constructor
// // QUESTION why double reference?
// Huge::Huge(Huge &&source)
// {
//     assert(source.mCapacity > 0);

//     mChunks = source.mChunks;
//     mLen = source.mLen;
//     mCapacity = source.mCapacity;

//     source.mChunks = nullptr;
//     source.mLen = 0;
//     source.mCapacity = 0;
// }

// // move assignment
// Huge &Huge::operator=(Huge &&source)
// {
//     assert(source.mCapacity > 0);

//     mChunks = source.mChunks;
//     mLen = source.mLen;
//     mCapacity = source.mCapacity;

//     source.mChunks = nullptr;
//     source.mLen = 0;
//     source.mCapacity = 0;

//     return *this;
// }
// // math operations
// bool Huge::IsZero() const
// {
//     AssertThis();

//     return (mLen == 1 && mChunks[0] == 0);
// }

// void Huge::Print() const
// {
//     AssertThis();
//     for (size_t i = 0; i < mLen; i++)
//     {
//         std::cout << " " << mChunks[i] << " ";
//     }
//     std::cout << "\n";
// }

// void Huge::Add(const Huge &huge)
// {
//     assert(mCapacity == huge.mCapacity && "in this program capacity between Huge objects HAVE TO be the same");
//     AssertThis();
//     huge.AssertThis();

//     // if our object has less lenght than huge then we...
//     if (mLen < huge.mLen)
//     {
//         // ...extent *this and fill it with zeros
//         for (std::size_t i = mLen; i < huge.mLen; i++)
//         {
//             mChunks[i] = 0;
//         }
//         // we adding so *this object is going to have huge lenght (if it is bigger)
//         mLen = huge.mLen;
//     }
//     UIntInternal remainder{0};
//     for (std::size_t i = 0; i < mLen; i++)
//     {
//         // mLen always bigger or equal to huge.mLen
//         UIntInternal hugeValue{(i < huge.mLen) ? huge.mChunks[i] : static_cast<UIntInternal>(0)};

//         // sum of remainder, huge value and *this
//         UIntInternal sum = mChunks[i] + hugeValue + remainder;

//         mChunks[i] = sum % hugeBase;
//         remainder = sum / hugeBase;

//         // if no remainder left and huge.mLen is already walked thru then we calculated addition
//         // we can return here
//         if (!remainder && i >= huge.mLen)
//             return;
//     }

//     if (remainder)
//     {
//         assert(mLen + 1 < mCapacity && "Overflow, resize is not implemented");

//         mChunks[mLen] = remainder;
//         mLen++;
//     }
// }

// // if base is too big then calculation may overflow internal variable, leading to wrong results
// void Huge::Multiply(UIntInternal num)
// {
//     AssertThis();

//     UIntInternal carry{0};

//     for (size_t i = 0; i < mLen; i++)
//     {
//         size_t multiplied = static_cast<size_t>(mChunks[i]) * num + carry;

//         mChunks[i] = multiplied % hugeBase;
//         carry = multiplied / hugeBase;
//     }

//     // num * mChunks[i] cannot overflow carry to the point we need to do iteration
//     if (carry > 0)
//     {
//         assert(mLen != mCapacity && "overflow will occur!!!");

//         mChunks[mLen] = carry;
//         mLen++;
//     }
// }

// void Huge::Divide(UIntInternal num)
// {
//     AssertThis();

//     UIntInternal borrow{0};

//     for (size_t i = 0; i < mLen; i++)
//     {
//         // reversed index
//         size_t index{mLen - i - 1};

//         // with cusve braces init compiler throws a lot of warnings
//         UIntInternal sum = borrow + mChunks[index];

//         UIntInternal division = sum / num;
//         UIntInternal remainder = sum % num;

//         mChunks[index] = division;

//         borrow = remainder * hugeBase;
//     }
//     // keep len to its required minimum
//     UIntInternal actualLen{};
//     for (size_t i = 0; i < mLen; i++)
//     {
//         if (mChunks[mLen - i - 1] != 0)
//         {
//             actualLen = mLen - i;
//             break;
//         }
//     }
//     // if zero then keep len to 1 
//     mLen = actualLen ? actualLen : 1;
// }

// UIntInternal Huge::CalcModule(UIntInternal num) const
// {
//     AssertThis();

//     UIntInternal borrow{};
//     UIntInternal remainder{};
//     for (size_t i = 0; i < mLen; i++)
//     {
//         // reversed index
//         size_t index{mLen - i - 1};

//         // with cusve braces init compiler throws a lot of warnings
//         UIntInternal sum = borrow + mChunks[index];

//         remainder = sum % num;

//         borrow = remainder * hugeBase;
//     }
//     return remainder;
// }

// #define HUGE_CAPACITY 1000
// #define MAX_CHAR_INPUT 1000

// // Can convert from 2 base to 36 base and everything in between
// class NumberConverter
// {
//     static char ToChar(const UIntInternal decimal)
//     {
//         if (decimal <= 9)
//             return decimal + '0';
//         else
//             return decimal + 'A' - 10;
//     }

//     static UIntInternal ToDecimal(const char digit)
//     {
//         if (digit >= 48 && digit <= 57)
//             return digit - '0';
//         else
//             return digit - 'A' + 10;
//     }

//     static void MultiplyInto(Huge &dest, const Huge &a, const UIntInternal b)
//     {
//         // copy assignment
//         dest = a;
//         dest.Multiply(b);
//     }

// public:
//     static Huge ParseStr(const std::string &str, const UIntInternal base)
//     {
//         size_t len = str.length();

//         Huge result{0, HUGE_CAPACITY};
//         Huge tmp{0, HUGE_CAPACITY};
//         Huge numDigit{1, HUGE_CAPACITY}; // numerical digit

//         for (size_t i = 0; i < len; i++)
//         {
//             UIntInternal decimal{ToDecimal(str[len - i - 1])};

//             MultiplyInto(tmp, numDigit, decimal);
//             result.Add(tmp);
//             numDigit.Multiply(base);
//         }

//         return result;
//     }

//     static std::string ToStr(const Huge &decimal, const UIntInternal base)
//     {
//         char tmp[MAX_CHAR_INPUT * 10];
//         size_t resultLen = 0;
//         Huge n{decimal};

//         do
//         {
//             UIntInternal remainder = n.CalcModule(base);

//             tmp[resultLen] = ToChar(remainder);
//             resultLen++;
//             n.Divide(base);
//         } while (!n.IsZero());

//         // reverse result string
//         for (size_t i = 0; i < resultLen / 2; i++)
//         {
//             char tmpchar{tmp[i]};
//             tmp[i] = tmp[resultLen - 1 - i];
//             tmp[resultLen - 1 - i] = tmpchar;
//         }

//         std::string result{};
//         result.assign(tmp, tmp + resultLen);
//         return result;
//     }
// };

// int main()
// {
//     int m{};
//     int k{};

//     std::cin >> m >> k;

//     std::string input{};
//     std::cin >> input;

//     Huge num = NumberConverter::ParseStr(input, static_cast<UIntInternal>(m));
//     std::string str = NumberConverter::ToStr(num, static_cast<UIntInternal>(k));
    
//     std::cout << str << std::endl;
// }