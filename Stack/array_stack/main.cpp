#include <iostream>

using namespace std;
class Stack {

private:
    int *stack;
    int count;

public:
    Stack() {
        stack = nullptr;
        count = 0;
    }

    void Push(int element) {
        int *tmp;
        tmp = stack;
        stack = new int[count + 1];

        for (int i = 0; i < count; i++)
            stack[i] = tmp[i];

        stack[count] = element;
        count++;
        if (count > 1)
            delete[] tmp;
    }

    int Pop() {
        if (count == 0)
            return 0;
        count--;
        return stack[count];
    }

    int Head() {
        if (count ==0)
            cout << "Is empty\n";
        else
            return stack[count - 1];
    }

    void Print() {
        int *ptr;
        ptr = stack;
        cout << "Stack: " << endl;
        if (count == 0)
            cout << "Is empty" << endl;

        for (int i = 0; i < count; i++) {
            cout << i << ") " << *ptr << endl;
            ptr++;
        }
    }

    ~Stack() {
        if (count > 0)
            delete stack;
    }
};

int main() {
    Stack st;
    cout << st.Head();
    st.Print();
    st.Push(45);
    st.Push(12);
    st.Push(89);
    st.Print();
    cout << st.Pop();
    st.Push(78);
    st.Print();
    st.Print();
    cout << st.Head();
    return 0;
}