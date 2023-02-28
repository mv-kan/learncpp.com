#include<iostream>

using namespace std;

class A {
    public: 
    int a = 10;
};

class B: private A {
    public:
    int a = 20;

};

int main() {
    B obj;
    A& rObj = obj;

    cout << rObj.a;
}