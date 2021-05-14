// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N. Требуется построить бинарное дерево,
// заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
// Выведите элементы в порядке level-order (по слоям, “в ширину”).

#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

struct Node {
    explicit Node(const int &val) : value(val) {}
    int value;
    shared_ptr<Node> left;
    shared_ptr<Node> right; // переписал как у вас в примере на фотке просто так потренироваться

//    ~Node()  {
//        cout << "~Node" << endl;
//    }
};

struct cmp {
    bool operator()(const int &left, const int &right) {return left <= right;}
};

template<class CMP>
class BinaryTree {
public:
    CMP cmp;
    shared_ptr<Node> root;
    explicit BinaryTree(CMP comp = CMP()) {
        cmp = comp;
    }

    void Insert(const int &value) {
        if (!root) {
            root = make_shared<Node>(value);
            return;
        }

        shared_ptr<Node> tree(root);
        while ((cmp(value, tree->value) && tree->left) || (!cmp(value, tree->value) && tree->right)) {
            if (cmp(value, tree->value))
                tree = tree->left;
            else
                tree = tree->right;
        }
        if (cmp(value, tree->value))
            tree->left = make_shared<Node>(value);
        else
            tree->right = make_shared<Node>(value);
    }

    void PrintBFS(function<void(const int &) > func) {
        return TraverseBFS([&func](const shared_ptr<Node> &node) {
            func(node->value);
        });
    }

    ~BinaryTree() {
        stack<shared_ptr<Node>> nodes;
        TraverseBFS([&nodes](const shared_ptr<Node> &node) {
            nodes.push(node);
        });
        while (!nodes.empty()) {
            auto current = nodes.top();
            if (current->left)
                current->left = nullptr;
            if (current->right)
                current->right = nullptr;
            nodes.pop();
        }
    }

private:
    void TraverseBFS(const function<void(shared_ptr<Node>)> &func) {
        if (!root)
            return;

        queue<shared_ptr<Node>> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            shared_ptr<Node> currentNode = nodes.front();
            nodes.pop();
            func(currentNode);
            if (currentNode->left)
                nodes.push(currentNode->left);
            if (currentNode->right)
                nodes.push(currentNode->right);
        }
    }
};

int main() {
    int size, value;
    cin >> size;
    BinaryTree<cmp> tree;
    for (int i = 0; i < size; i++) {
        cin >> value;
        tree.Insert(value);
    }
    tree.PrintBFS([](const int &value) {
        cout << value << " ";
    });
    return 0;
}