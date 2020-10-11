#include <iostream>
#include "HuffTree.hpp"
#include "Codec.hpp"

int main(int argc, char** argv)
{
    auto res = Stats("/home/Pro/huffman/test.txt");
    auto ht = CreateHuffTree(res);
    auto map = CreateHuffMap(ht);
    ht->Release();
    delete ht;

    Compress("/home/Pro/huffman/test.txt", "/home/Pro/huffman/test.bin");

    // std::fstream fst("out.txt", std::fstream::binary | std::fstream::out | std::fstream::app);
    // fst << "AVC";
    // fst << 65;
    // uint8_t d = 66;
    // fst.write(reinterpret_cast<char*>(&d), sizeof(d));
    return 0;
}