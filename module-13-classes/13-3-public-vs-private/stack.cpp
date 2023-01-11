#include <iostream>
#include <cassert>
// PROJECT stack

class Stack {
    static constexpr int stackSize{10};
    int m_arr[stackSize]{};
    // size of stack, i.e. point to last element in @m_array
    int m_size{};
public:
    void reset() {
        m_size = 0;
    }
    bool push(int n) {
        if (m_size >= 10)
            return false;
        
        m_arr[m_size] = n;
        m_size++; // this is size, index = size - 1
        return true;
    }
    int pop() {
        assert(m_size == 0 || "Stack is empty");

        m_size--; // this is size, index = size - 1
        return m_arr[m_size];
    }
    void print() {
        std::cout << "( ";
        for (int i = 0; i < m_size; i++)
        {
            std::cout << m_arr[i] << ", ";
        }
        std::cout << ')' << std::endl;
    }
};


int main()
{
	Stack stack;
	stack.print();

	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();

	stack.print();

	return 0;
}