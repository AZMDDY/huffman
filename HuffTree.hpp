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
    uint16_t chr;
    uint32_t weight;
    HuffChar(uint16_t c, uint32_t w = 0) : chr(c), weight(w) {}
    bool operator<(const HuffChar& hc) const
    {
        if (weight == hc.weight) {
            return (chr > hc.chr);
        }
        else {
            return (weight > hc.weight);
        }
    }
};

using HuffNode = Node<HuffChar>;

#endif  // HUFF_TREE_HPP_