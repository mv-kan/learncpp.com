#include <iostream>


int main() {
    int result{system("make run_one SRC=./module-0/helloworld.cpp")};
    if (result != 0) 
        exit(1);
    
    return result;
}