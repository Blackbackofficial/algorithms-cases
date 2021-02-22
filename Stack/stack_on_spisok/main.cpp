// Стек и его класс
#include "iostream"

struct Stack {
    int value = 0;
    Stack * next = nullptr;
};

class STACK {
private:
    Stack *stack;
    unsigned int count = 0;

public:

    void push(int element) {
        Stack *ptr;
        ptr = new Stack;
        ptr->next = stack;
        ptr->value = element;
        stack = ptr;
        count++;
    }

    void pop() {
        if (stack == nullptr) {
            std::cout << "Is empty!\n";
        } else {
            if (stack->next != nullptr) {
                stack->value = stack->next->value;
                stack->next = stack->next->next;
                count--;
            } else {
                stack = nullptr;
            }
        }
    }

    bool empty() const {
        if (stack->next != nullptr) {
            return false;
        } else {
            return true;
        }

    }

    void print_stack() {
        Stack *ptr;
        ptr = stack;
        for (int i = 0; i < count; i++) {
            std::cout << i << ") " << ptr->value << std::endl;
            ptr = ptr->next;
        }
    }

};


int main() {
    STACK node;
    node.pop();
    node.push(2);
    node.push(4);
    node.push(9);
    node.push(3);
    node.pop();
    node.push(89);
//    int q = node.empty();
//    std:: cout << q << std::endl;
    node.print_stack();
    return 0;
}