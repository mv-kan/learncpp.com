#include <iostream>

using namespace std;
// move constructor
class Arr {
    int*arr = nullptr;
    int size = 0;
    void allocate(int nSize, int value) {
        size = nSize;
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = value;
        }
    } 
    void deallocate() 
    {
        if (arr)
            delete[] arr;
    }
    void copy(const Arr& obj) 
    {
        size = obj.size;
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
           arr[i] = obj.arr[i];
        }
    }
public:
    Arr(int nSize){
        allocate(nSize, 0);
    }
    Arr(int nSize, int value) {
        allocate(nSize, value);
    }
    Arr(const Arr& obj){
        cout << "Copy constructor" << endl;
        copy(obj);
    }
    void Init(int nVal) const {
        for (int i = 0; i < size; i++)
        {
            arr[i] = nVal;
        }
        
    }
    void Show() {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << '\t';
        }
        cout << endl;
    }
    ~Arr() {
        deallocate();
    }
    Arr& operator=(const Arr& obj) {
        // to prevent self copying 
        if (this == &obj)
            return *this;
        deallocate();
        copy(obj);
        return *this;
    }
};

int main() {
    Arr obj{3, 5};
    Arr obj2{5, 10};

    cout << "obj: \t\t";
    obj.Show();
    cout << "obj2: \t\t";
    obj2.Show();
    obj = obj2;
    cout << "obj = obj2: \t";
    obj.Show(); 
}