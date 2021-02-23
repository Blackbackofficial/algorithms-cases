// Список односвязанный и reverse метод
#include "iostream"
struct Node {
    int data;
    Node * next;
};

class NODE {

private:
    Node *sp;

public:
    NODE(int element) {
        Node *node = new Node;
        node->data = element;
        node->next = nullptr;
        sp = node;
    }

    void push(int element, int position) {
        Node * ptr, *spp;
        spp = sp;
        ptr = new Node;
        for (int i = 0; i < position - 1; i++) {
            if (spp->next != nullptr) {
                spp = spp->next;
            }
        }
        ptr->data = element;
        ptr->next = spp->next;
        spp->next = ptr;
    };

    void pop(int element) {
        Node * current;
        current = sp;
        for (int i = 0; i < element; i++) {
            if (current->next != nullptr)
                current = current->next;
        }
        current = current->next;
        sp = current;
    }

    void reverse() {
        Node *next, * current, *prev;
        prev = nullptr;
        current = sp;
        while(current != nullptr) {
            next =current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        sp = prev;
    }

    void print_sp() {
        Node * ptr;
        ptr = sp;
        int i = 0;
        while (ptr->next != nullptr) {
            std::cout << i << ") " << ptr->data << std::endl;
            ptr = ptr->next;
            i++;
            if (ptr->next == nullptr)
                std::cout << i << ") " << ptr->data << std::endl;
        }
    }
};
int main() {
    NODE sp{33};
    sp.push(1, 1);
    sp.push(2, 2);
    sp.push(3, 3);
    sp.reverse();
    sp.print_sp();
    sp.reverse();
    sp.pop(0);
    sp.pop(2);
    sp.print_sp();
    return 0;
}