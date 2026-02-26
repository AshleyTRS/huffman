#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct FreqNode
{
    long long freq;
    char symbol;
    int elem_no;
};

class Huffman
{
public:
    explicit Huffman(const std::string &input);

    const std::vector<FreqNode> &frequency_table() const;
    const std::unordered_map<char, std::string> &codes() const;
    std::string encode() const;
    std::string decode(const std::string &encoded) const;

    struct Node
    {
        long long freq;
        char symbol;
        long long priority;
        Node *left;
        Node *right;

        Node(long long f, char c, long long p);
    };

        void build_frequency_table();
    void build_tree();
    void build_codes(Node *node, const std::string &prefix);

    std::string input_;
    Node *root_;
    Node *root() const;
    std::vector<FreqNode> freq_table_;
    std::unordered_map<char, std::string> codes_;
};