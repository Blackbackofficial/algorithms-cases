// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N. Требуется построить бинарное дерево,
// заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
// Выведите элементы в порядке level-order (по слоям, “в ширину”).

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct cmp {
    bool operator()(const int& left, const int& right) {return left <= right;}
};

template<class CMP>
class BinaryTree {
public:
    CMP cmp;
    int root;
    explicit BinaryTree(int value, CMP comp = CMP()) {
        root = value;
        cmp = comp;
        left = nullptr;
        right = nullptr;
    }

    ~BinaryTree() = default;

    void Insert(int value) {
        BinaryTree * tree = this;

        while (true) {
            if (cmp(tree->root, value)) {
                if (tree->left == nullptr) {
                    tree->left = new BinaryTree(value);
                    break;
                } else
                    tree = tree->left;
            } else {
                if (tree->right == nullptr) {
                    tree->right = new BinaryTree(value);
                    break;
                } else
                    tree = tree->right;
            }
        }
    }

    void TraverseBFS() {
        deque <BinaryTree*> currentBFS;
        deque <int> endBFS;

        currentBFS.push_back(this);

        while (!currentBFS.empty()) {
            BinaryTree * current = currentBFS.front();

            if (current->right)
                currentBFS.push_back(current->right);
            if (current->left)
                currentBFS.push_back(current->left);

            endBFS.push_back(current->root);
            currentBFS.pop_front();
        }

        for (int i : endBFS)
            cout << i << " ";
    }

private:
    BinaryTree * left;
    BinaryTree * right;
};

int main() {
    int size, value;
    cin >> size;
    cin >> value;
    BinaryTree<cmp> tree(value);

    for (int i = 0; i < size - 1; i++) {
        cin >> value;
        tree.Insert(value);
    }

    tree.TraverseBFS();
    return 0;
}