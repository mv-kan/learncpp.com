#include<iostream>

using namespace std;

class Animal
{
protected:
    string name; 
public:
    Animal(): name("animal"){
        cout << "Animal()" << endl;
    }

    virtual void Do() {
        cout << name << ": no specific voice" << endl;    
    }
};

class Dog: public Animal
{
public:
    Dog() {
        name = "Dog";
        cout << "Dog()" << endl;
    }

    void Do() {
        cout << name << ": Bark BARK BARK" << endl;    
    }
};

class Cat: public Animal 
{
public:
    Cat() {
        name = "Cat";
        cout << "Cat()" << endl;
    }
    void Do() {
        cout << name << ": Meow" << endl;    
    }
};

int main() {
    Animal* aniptr;
    Dog dog;
    Cat cat; 

    aniptr = &dog;
    aniptr->Do();

    aniptr = &cat;
    aniptr->Do();

    Animal& aniref = dog;

    aniref.Do();

    aniref = cat;
    aniref.Do();
    int a{5}, b{10};
    int& ref = a;
    ref = b;
    cout << ref << endl;
}