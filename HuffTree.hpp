#ifndef HUFF_TREE_HPP_
#define HUFF_TREE_HPP_
#include "BinTree.hpp"
struct HuffChar {
    char chr;
    unsigned int weight;
    HuffChar(char c, unsigned int w = 0) : chr(c), weight(w) {}
    bool operator<(const HuffChar& hc)
    {
        // 颠倒
        return (this->weight > hc.weight);
    }
    bool operator>(const HuffChar& hc)
    {
        // 颠倒
        return (this->weight < hc.weight);
    }
    bool operator==(const HuffChar& hc)
    {
        return (this->weight == hc.weight);
    }
};

using HuffTree = BinTree<HuffChar>;

#endif  // HUFF_TREE_HPP_