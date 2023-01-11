#include <iostream>
#include <sstream>
#include <string>
// $ make run_one_args SRC=./module-12/12-5-command-line-arguments/parsing_int.cpp ARGS="1232"
int main(int argc, char* argv[]) {
    if (argc <= 1) {
        if (argv[0]) {
            std::cout << "Usage: " << argv[0] << "<number>\n";
        } else {
            std::cout << "Usage: " << "<program name> <number>\n";
        }
    }
    std::stringstream convert{argv[1]};
    
    int myint{};
    if (!(convert >> myint)) {
        myint = 0;
    }
    std::cout << "Your int: " << myint << std::endl;
    return 0;
} 
