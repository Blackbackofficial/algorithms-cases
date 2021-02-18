#include "iostream"

struct List {
    int value = 0;
    List * next = nullptr;
    List * parent = nullptr;
};

void add_value_end(List * node, int element){
    if (node->next == nullptr) {
        node->value = element;
        node->next = new List;
    } else {
        List * l = node;
        List * parent;
        while (l->next != nullptr) {
            parent = l;
            l = l->next;
        }
        l->next = new List;
        l->value = element;
        l->parent = parent;
    }
}

void add_value_start(List * first, int element) {
    List *pw;
    pw = new List;
    pw->next = first->next;
    pw->value = first->value;
    pw->parent = first;
    first->value = element;
    first->next = pw;
}

void delete_element_list(List * node, int element) {
    List * ptr = node;
    int i = 0;
    while (ptr->next != nullptr) {
        if (i == element ) {
            if (ptr->parent == nullptr) {
                *ptr = *ptr->next;
                break;
            } else if (ptr->next != nullptr) {
                ptr->parent->next = ptr->next;
                ptr->next->parent = ptr->parent;
                break;
            }
        } else {
            ptr = ptr->next;
            i++;
        }
    }
    if (ptr->next == nullptr)
        std::cout << "It isn't number list\n";
    if (i > 0)
        delete[] ptr;
}

void add_to_middle(List * node, int element, int position) {
    List * ptr = node;
    int i = 0;
    while (ptr->next != nullptr) {
        if (position == i) {
            if (ptr->parent == nullptr) {
                add_value_start(ptr, element);
                break;
            } else {
                List *newList = new List;
                newList->next = ptr;
                newList->parent = ptr->parent;
                newList->value = element;
                ptr->parent->next = newList;
                ptr->parent = newList;
                break;
            }

        } else {
            ptr = ptr->next;
            i++;
        }
    }
    if (ptr->next == nullptr) {
        add_value_end(ptr, element);
        std::cout << "We add new value to end because [element] > List[]\n";
    }
}

void print_list(List * node){
    List * print;               // нужно создать копию иначе мы перезапишем List
    print = node;
    int num = 0;
    std::cout << "List:\n";
    while (print->next != nullptr) {
        std::cout << num << ") " << print->value << std::endl;
        num++;
        print = print->next;
    }
}

int main() {
    List list;
    add_value_end(&list, 321);
    add_value_end(&list, 123);
    add_value_end(&list, 213);
    add_value_start(&list, 18888);
    print_list(&list);
    delete_element_list(&list, 1);
    add_to_middle(&list, 89, 1);
    add_to_middle(&list, 11, 3);
    print_list(&list);
    return 0;
}