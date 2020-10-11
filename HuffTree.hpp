#ifndef HUFF_TREE_HPP_
#define HUFF_TREE_HPP_

#include <algorithm>

template <typename T>
struct Node {
    Node<T>* left;
    Node<T>* right;
    T val;
    Node(const T& val, Node<T>* l = nullptr, Node<T>* r = nullptr) : left(l), right(r), val(val) {}
    ~Node() {}
    void Release()
    {
        if (left != nullptr) {
            left->Release();
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            right->Release();
            delete right;
            right = nullptr;
        }
    }
    bool operator<(const Node<T>& node) const
    {
        return (val < node.val);
    }
};

struct HuffChar {
    char chr;
    int weight;
    HuffChar(char c, int w = 0) : chr(c), weight(w) {}
    bool operator<(const HuffChar& hc) const
    {
        return (weight > hc.weight);
    }
};

using HuffNode = Node<HuffChar>;

#endif  // HUFF_TREE_HPP_