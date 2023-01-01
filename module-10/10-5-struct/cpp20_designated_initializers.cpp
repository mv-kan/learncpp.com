struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    return 0;
}