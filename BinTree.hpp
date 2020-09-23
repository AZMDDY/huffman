#ifndef BIN_TREE_HPP_
#define BIN_TREE_HPP_

template <typename T>
struct Node {
    Node* left;
    Node* right;
    T val;
    Node(const T& val) : left(nullptr), right(nullptr), val(val) {}
};

template <typename T>
class BinTree {
    
};

#endif  // BIN_TREE_HPP_