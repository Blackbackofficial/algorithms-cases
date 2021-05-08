// 5. Алгоритм сжатия данных Хаффмана
// Напишите две функции для создания архива из одного файла и извлечения файла из архива.
// Требования: коэффициент сжатия < 1.

#include "Huffman.h"
#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <fstream>
#include <map>
#include <cmath>


using namespace std;

struct Node {
    char letter;
    int frequency;
    Node * _left;
    Node * _right;
    Node() = default;
    Node(char c): letter(c), _left(0), _right(0) {};

    Node(Node * left, Node * right): letter(0), _left(left), _right(right) {};

    Node(char x, int y, Node * left = nullptr, Node * right = nullptr):
            letter(x), frequency(y), _left(left), _right(right) {};

    ~Node() {
        delete _left;
        delete _right;
    }
};

struct Comparison {
    bool operator ()(Node * left, Node * right) {
        return left->frequency < right->frequency;
    }
};

///
void Builder(Node * root, vector <bool> &bits, map <char, vector<bool>> &code);
void Parser(Node * root, IOutputStream &compressed);
Node * UnParser(IInputStream &compressed);

void Builder(Node * root, vector<bool> &bits, map<char,vector<bool>> &code) {
    if (!root)
        return;
    if (!root->_left && !root->_right)
        code[root->letter] = bits;
    if (root->_right) {
        bits.push_back(1);
        Builder(root->_right, bits, code);
    }
    if (root->_left) {
        bits.push_back(0);
        Builder(root->_left, bits, code);
    }
    bits.pop_back();
}

void Parser(Node * root, IOutputStream &compressed) {
    if (!root)
        return;
    Parser(root->_left, compressed);
    Parser(root->_right, compressed);
    if (!root->_left && !root->_right) {
        compressed.Write('1');
        compressed.Write(root->letter);
    } else
        compressed.Write('0');
}

Node * UnParser(IInputStream &compressed) {
    char charSize;
    int intSize;

    compressed.Read(charSize);
    intSize = (unsigned char)charSize;
    compressed.Read(charSize);
    intSize += (int)((unsigned char)charSize) << 8;

    stack<Node*> stack1;
    long current = 0;
    char symbol;

    while (current < intSize || stack1.size() > 1) {
        compressed.Read(symbol);
        if (symbol == '1') {
            compressed.Read(symbol);
            current++;
            Node * data = new Node(symbol);
            stack1.push(data);
        } else {
            if (symbol == '0') {
                Node * x = stack1.top();
                stack1.pop();
                Node * y = stack1.top();
                stack1.pop();

                Node * data = new Node(y, x);
                stack1.push(data);
            }
        }
    }
    Node * root;

    if (!stack1.empty())
        root = stack1.top();
    stack1.pop();
    return root;
}

void Encode(IInputStream &original, IOutputStream &compressed) {
    map<char, int> frequency;
    long line = 0;
    char c;
    string file;

    while (original.Read(c)) {
        frequency[c]++;
        file += c;
    }
    list<Node*> leaflet;

    for (auto & frequence : frequency) {
        Node * node = new Node(frequence.first, frequence.second, 0, 0);
        leaflet.push_back(node);
    }
    if (leaflet.empty())
        return;
    while (leaflet.size() != 1) {
        leaflet.sort(Comparison());
        Node * L = leaflet.front();
        leaflet.pop_front();
        Node * R = leaflet.front();
        leaflet.pop_front();

        Node * parent = new Node(0, L->frequency + R->frequency, L, R);
        leaflet.push_back(parent);
    }
    Node * root = leaflet.front();
    char buffer = 0;
    long count = 0;

    vector<bool> bits;
    map<char,vector<bool>> coded;
    Builder(root, bits, coded);
    long fileSize = file.size();

    for (int i = 0; i < 8; ++i) {
        char ch = (fileSize >> (i * 8));
        compressed.Write(ch);
    }

    long size = coded.size();
    compressed.Write(size);
    compressed.Write(size >> 8);
    Parser(root, compressed);

    while (line < file.size()) {
        c = file[line];
        line++;
        vector<bool> x = coded[c];
        for (auto && i : x) {
            buffer = buffer | (i << (7 - count));
            count++;
            if (count == 8) {
                count = 0;
                compressed.Write(buffer);
                buffer = 0;
            }
        }
    }
    compressed.Write(buffer);
    delete root;
}

void Decode (IInputStream &compressed, IOutputStream &original) {
    long cfile = 0;
    long filesize = 0;

    for (int i = 0; i < 8; i++) {
        char symbol;
        compressed.Read(symbol);

        if (symbol < 0) {
            filesize += pow(256, i) * (256 + symbol);
        }
        else {
            if (symbol > 0) {
                filesize += pow(256, i) * symbol;
            }
        }
    }

    Node * root = UnParser(compressed);
    Node * node = root;
    if (!root)
        return;

    int count = 0;
    char symbol;
    char buffer;
    vector<bool> bits;
    map<char, vector<bool>> code;
    Builder(root, bits, code);
    compressed.Read(symbol);

    while (cfile < filesize) {
        bool bit = symbol & (1 << (7 - count++));

        if (bit)
            node = node->_right;
        else
            node = node->_left;

        if (!node)
            return;

        if (!node->_left && !node->_right) {
            original.Write(node->letter);
            buffer = node->letter;
            cfile++;
            node = root;
        }

        if (count == 8)
            count = 0;
        compressed.Read(symbol);
    }
    delete root;
}