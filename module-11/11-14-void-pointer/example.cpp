int main () {
    int value{ 5 };
    void* voidPtr{ &value };

    // std::cout << *voidPtr << '\n'; // illegal: dereference of void pointer

    int* intPtr{ static_cast<int*>(voidPtr) }; // however, if we cast our void pointer to an int pointer...

    std::cout << *intPtr << '\n'; // then we can dereference the result
}