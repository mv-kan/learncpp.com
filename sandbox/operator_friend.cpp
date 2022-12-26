#include <iostream>

class Number {
    int val;
public:
    Number(int nVal): val(nVal) {

    }
    Number(const Number& n): val(n.val) {

    }
    Number operator=(const Number& n) {
        val = n.val;
        return *this;
    }

    friend Number operator-(Number& obj, Number& obj2) {
        Number temp{obj.val - obj2.val};
        return temp;
    }
    friend void ShowContent(const Number& obj);
    
    friend Number operator-(int n, const Number& obj);
};
Number operator- (int n, const Number& obj) {
    Number temp{ n - obj.val};
    return temp;
}

void ShowContent(const Number& obj) {
    std::cout << obj.val << std::endl; 
}

int main() {
    Number n{1};
    Number n2{1};
    ShowContent(n);
    Number n3{n - n2};
    ShowContent(n3);
    ShowContent(123 - n);

    std::cout << 123 + 23 << std::endl;
    
}