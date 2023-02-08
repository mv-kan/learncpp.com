#include<iostream>
using namespace std;
class InnerClass {
    public:
    InnerClass() {
        cout << "InnerClass\n";
    }
    ~InnerClass() {
        cout << "~InnerClass\n";
    }
};

class MyClass {
    InnerClass a; 
    public:
    MyClass() {
        cout << "MyClass\n";
    }
    ~MyClass() {
        cout << "~MyClass\n";
    }
};

int main(){
    MyClass*a = new MyClass();

    delete a;
}