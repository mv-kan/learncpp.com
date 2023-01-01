#include <iostream>
using namespace std;
template<typename T>
struct Triad {
    T a{};
    T b{};
    T c{};
};


template <typename T>
Triad(T, T, T) -> Triad<T>;

template<typename T>
void printTriad(Triad<T> t) {
    cout << "[ " << t.a << ", " <<  t.b << ", " <<  t.b << " ]" << endl;
}

int main() {
    Triad t1{1, 2, 3};
    Triad t2{1.2, 2.3, 3.4};

    printTriad(t1);
    printTriad(t2);
    return 0;
}