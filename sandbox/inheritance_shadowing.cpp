#include<iostream>

using namespace std;

class A {
};

class B: private A {

};

int main() {
    // B obj;
    // A& rObj = obj;

    // cout << rObj.a;

    A* a = new B();
    delete a;
}