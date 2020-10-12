#include <iostream>
#include "HuffTree.hpp"
#include "Codec.hpp"

int main(int argc, char** argv)
{
    auto res = Stats("/home/Pro/huffman/test.txt");
    auto ht = CreateHuffTree(res);
    auto map = CreateHuffMap(ht);

    Compress("/home/Pro/huffman/test.txt", "/home/Pro/huffman/test.bin");

    Decompress("/home/Pro/huffman/test.bin", ht, "test1.txt");

    ht->Release();
    delete ht;
    return 0;
}