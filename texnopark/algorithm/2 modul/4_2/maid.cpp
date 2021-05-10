// Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел,
// а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A,
// команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается
// числом k. Требуемая скорость выполнения запроса - O(log n).
#include <iostream>
#include <cassert>

struct cmp {
    bool operator()(const int& left, const int& right) {return left > right;}
};

class CNode {
public:
    explicit CNode (int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
        number = 1;
    };
    ~CNode() = default;

    int data;
    CNode *left;
    CNode *right;
    uint8_t height;
    int number;
};

template<class CMP>
class AVLNode {
public:
    CNode* root;
    CMP cmp;
    explicit AVLNode(CMP comp = CMP()) {
        cmp = comp;
        root = nullptr;
    };
    ~AVLNode() = default;

    [[nodiscard]] int KStatic(int k) const {
        CNode * current = root;

        while (current) {
            int t = current->left ? current->left->number : 0;

            if (t == k)
                return current->data;

            if (t > k)
                current = current->left;
            else {
                current = current->right;
                k = k - 1 - t;
            }
        }
        return -1;
    };

    void StartAVL(int data) {
        Insert(root, data);
    }

    void DeleteAVL(int data) {
        DeleteNode(root, data);
    }

private:
    static int balance_ratio(CNode * node) {
        return (node->right ? node->height : 0) - (node->left ? node->height : 0);
    };

    static void rename(CNode * node) {
        int h_left = node->left ? node->height : 0;
        int h_right = node->right ? node->height : 0;

        (h_left > h_right) ? node->height = h_left + 1 : node->height = h_right + 1;

        int n_left = node->left ? node->left->number : 0;
        int n_right = node->right ? node->right->number : 0;
        node->number = n_left + n_right + 1;

    };

    static CNode * small_right(CNode * node) {
        CNode * tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        rename(node);
        rename(tmp);

        return tmp;
    };

    static CNode * small_left(CNode* node) {
        CNode* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        rename(node);
        rename(tmp);

        return tmp;
    };

    static CNode * balance(CNode * node) {
        rename(node);

        int ratio = balance_ratio(node);

        if (ratio == 2) {
            if (balance_ratio(node->right) < 0)
                node->right = small_right(node->right);
            return small_left(node);
        }

        if (ratio == -2) {
            if (balance_ratio(node->left) > 0)
                node->left = small_left(node->left);
            return small_right(node);
        }
        return node;
    };

    void Insert(CNode*& node, int value) {
        if (node == nullptr) {
            node = new CNode(value);
            return;
        }

        (cmp(node->data, value)) ? Insert(node->left, value) :Insert(node->right, value);

        node = balance(node);
    };

    static CNode * FindMaximum(CNode* node) {
        assert(node != nullptr);
        while (node->right)
            node = node->right;

        return node;
    };

    void DeleteNode(CNode*& node, int data) {
        if (cmp(node->data, data))
            DeleteNode(node->left, data);

        if (node->data < data)
            DeleteNode(node->right, data);

        if (node->data == data) {
            if (!(node->left) || !(node->right)){
                CNode* check = node->left? node->left : node->right;
                if (check)
                    *node = *check;
                else {
                    check = node;
                    node = nullptr;
                }
                delete check;
            } else {
                CNode* check = FindMaximum(node->left);
                node->data = check->data;
                DeleteNode(node->left, check->data);
            }
        }

        if (!node)
            return;
        balance(node);
    };
};

int main() {
    AVLNode<cmp> AVLTree;
    int size, value, j;
    std::cin >> size;

    for (int i = 0; i < size; i++) {
        std::cin >> value >> j;
        (value > 0) ? AVLTree.StartAVL(value) : AVLTree.DeleteAVL(std::abs(value));
        std::cout << AVLTree.KStatic(j) << " ";
    }

    return 0;
}
//5
//40 0
//10 1
//4 1
//-10 0
//50 2