class Foo
{
private:

public:
    Foo()
    {
        // code to do A
    }

    Foo(int value): Foo{} // use Foo() default constructor to do A
    {
        // code to do B
    }

};