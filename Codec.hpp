#ifndef CODEC_HPP_
#define CODEC_HPP_

#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <functional>
#include <unordered_map>
#include "HuffTree.hpp"

static uint16_t uChr = 256;

std::string ReadFile(const std::string& fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cout << "file open failed!" << std::endl;
        return "";
    }
    std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    return std::move(data);
}

void WriteFile(const std::string& content, const std::string& fileName)
{
    std::ofstream ofs(fileName);
    if (ofs.is_open()) {
        ofs << content;
        ofs.close();
    }
}

// 统计文件中字符出现的频率
std::priority_queue<HuffNode> Stats(const std::string& fileName)
{
    auto data = ReadFile(fileName);

    std::vector<uint32_t> chrFreq(256, 0);
    for (auto& c : data) {
        chrFreq[static_cast<uint8_t>(c)]++;
    }
    std::priority_queue<HuffNode> res;
    for (uint16_t i = 0; i < chrFreq.size(); i++) {
        if (chrFreq[i] != 0) {
            res.emplace(HuffChar(static_cast<uint16_t>(i), chrFreq[i]));
        }
    }
    return std::move(res);
}

HuffNode* CreateHuffTree(std::priority_queue<HuffNode>& chrFreq)
{
    while (chrFreq.size() != 1) {
        auto left = new HuffNode(chrFreq.top());
        chrFreq.pop();
        auto right = new HuffNode(chrFreq.top());
        chrFreq.pop();
        chrFreq.emplace(HuffChar(uChr, left->val.weight + right->val.weight), left, right);
    }
    auto root = chrFreq.top();
    chrFreq.pop();
    return new HuffNode(root.val, root.left, root.right);
}

std::vector<std::vector<bool>> CreateHuffMap(HuffNode* root)
{
    std::vector<std::vector<bool>> huffMap(256);
    std::stack<HuffNode*> stk;
    std::vector<bool> tmp;
    auto node = root;

    std::function<void(HuffNode*, std::vector<bool>&, std::vector<std::vector<bool>>&)> dfs =
        [&](HuffNode* node, std::vector<bool>& tmp, std::vector<std::vector<bool>>& res) {
            if (node == nullptr) {
                return;
            }
            if (node->left == nullptr && node->right == nullptr) {
                res[node->val.chr] = tmp;
                return;
            }
            auto lTmp = tmp;
            auto rTmp = tmp;
            lTmp.push_back(false);
            rTmp.push_back(true);
            dfs(node->left, lTmp, res);
            dfs(node->right, rTmp, res);
        };

    dfs(node, tmp, huffMap);
    return huffMap;
}

void Compress(const std::string& inFile, const std::string& outFile)
{
    auto chrFreq = Stats(inFile);
    auto huffTree = CreateHuffTree(chrFreq);
    auto huffMap = CreateHuffMap(huffTree);
    huffTree->Release();
    delete huffTree;
    auto data = ReadFile(inFile);

    std::fstream fst(outFile, std::fstream::binary | std::fstream::out);

    uint8_t buf = 0;
    int count = 0;
    for (auto& c : data) {
        auto val = huffMap[static_cast<int>(c)];
        for (auto bit : val) {
            std::cout << bit;
            buf = buf | (static_cast<int>(bit) << (7 - count));
            count++;
            if (count == 8) {
                // std::cout << int(buf) << std::endl;
                fst.write(reinterpret_cast<char*>(&buf), sizeof(buf));
                buf = 0;
                count = 0;
            }
        }
    }
    std::cout << std::endl;
    if (count != 0) {
        fst.write(reinterpret_cast<char*>(&buf), sizeof(buf));
    }
}

void Decompress(const std::string& inFile, HuffNode* root, const std::string& outFile)
{
    auto data = ReadFile(inFile);
    auto node = root;
    std::string res = "";
    std::string dataBit;
    for (auto& c : data) {
        std::stringstream ss;
        for (int i = 7; i >= 0; i--) {
            ss << ((c >> i) & 1);
        }
        dataBit += ss.str();
    }
    std::cout << dataBit << std::endl;
    int i = 0;
    while (i < dataBit.size()) {
        if (dataBit[i] == '0' && node->left != nullptr) {
            node = node->left;
            i++;
        }
        else if (dataBit[i] == '1' && node->right != nullptr) {
            node = node->right;
            i++;
        }
        if (node->left == nullptr && node->right == nullptr) {
            std::cout << node->val.chr;
            res += node->val.chr;
            node = root;
        }
    }
    std::cout << "\n" << res << std::endl;
    WriteFile(res, outFile);
}

#endif  // CODEC_HPP_