#include<iostream>

using namespace std;


// abstract class, because it has at least one pure virtual function 
// if no implementation found in child class then this child class is abstract class too
class Animal
{
protected:
    string name; 
public:
    Animal(): name("animal"){
        cout << "Animal()" << endl;
    }
    virtual ~Animal() {
        cout << "~Animal()" << endl;
    }
    virtual void Do() = 0;
};

class Dog: public Animal
{
public:
    Dog() {
        name = "Dog";
        cout << "Dog()" << endl;
    }
    ~Dog() {
        cout << "~Dog()" << endl;
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
    ~Cat() {
        cout << "~Cat()" << endl;
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
    // ref
    int a{5}, b{10};
    int& ref = a;
    ref = b;
    cout << ref << endl;
    
    // dynamic 
    cout << "dynamic\n\n";
    Animal* ptr = new Dog();
    ptr->Do();

    delete ptr;
    cout << "enddynamic\n\n";

}