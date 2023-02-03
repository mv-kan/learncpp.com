#include <iostream>
class IntArray
{
public:
    // constructor
    IntArray(size_t len = 0) : mLen{len}
    {
        for (size_t i = 0; i < len; i++)
        {
            mArr[i] = 0;
        }
    }

    // copy constructor
    IntArray(const IntArray &that)
    {
        mLen = that.mLen;
        for (size_t i = 0; i < that.mLen; i++)
        {
            (*this)[i] = that[i];
        }
    }
    // copy assignment
    IntArray &operator=(const IntArray &that)
    {
        for (size_t i = 0; i < that.mLen; i++)
        {
            (*this)[i] = that[i];
        }
        mLen = that.mLen;
         return *this;
    }

    int &operator[](size_t i)
    {
        return mArr[i];
    }
    int operator[](size_t i) const
    {
        return mArr[i];
    }
    friend std::ostream &operator<<(std::ostream &out, const IntArray &arr)
    {
        for (size_t i = 0; i < arr.mLen; i++)
        {
            out << arr[i] << " ";
        }
        return out;
    }

    // destructor
private:
    // QUESTION static mem in dynamic obj how can be?
    int mArr[100];
    size_t mLen{0};
};

IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}

int main()
{
    IntArray a{fillArray()};
    std::cout << a << '\n';

    auto &ref{a}; // we're using this reference to avoid compiler self-assignment errors
    a = ref;

    IntArray b(1);
    b = a;

    std::cout << b << '\n';

    return 0;
}