#include "Huffman.hpp"
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <set>

Huffman::Node::Node(long long f, char c, long long p)
    : freq(f), symbol(c), priority(p), left(nullptr), right(nullptr) {}

Huffman::Huffman(const std::string &input)
    : input_(input), root_(nullptr)
{
    build_frequency_table();
    build_tree();
    build_codes(root_, "");
}

Huffman::Node *Huffman::root() const
{
    return root_;
}

const std::vector<FreqNode> &Huffman::frequency_table() const
{
    return freq_table_;
}

const std::unordered_map<char, std::string> &Huffman::codes() const
{
    return codes_;
}

std::string Huffman::encode() const
{
    std::string result;
    for (char c : input_)
        result += codes_.at(c);
    return result;
}

std::string Huffman::decode(const std::string &encoded) const
{
    std::string result;
    Node *curr = root_;

    for (char bit : encoded)
    {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right)
        {
            result += curr->symbol;
            curr = root_;
        }
    }
    return result;
}

void Huffman::build_frequency_table()
{

    std::unordered_map<char, long long> idx_tracker;
    std::set<char> seen_chars;
    int curr_idx = 0;

    for (char c : input_)
    {
        if (seen_chars.find(c) != seen_chars.end())
        { // symbol has already been found
            int idx = idx_tracker[c];
            freq_table_[idx].freq++;
        }
        else
        { // new symbol discovered -> add to set
            seen_chars.insert(c);
            // assign idx to symbol
            idx_tracker[c] = curr_idx;
            // add symbol to frequency table
            FreqNode node = {1, c, curr_idx};
            freq_table_.push_back(node);
            // create next idx
            curr_idx++;
        }
    }

    std::sort(freq_table_.begin(), freq_table_.end(),
              [](const FreqNode &a, const FreqNode &b)
              {
                  if (a.freq == b.freq)
                  {
                      return a.elem_no < b.elem_no;
                  }
                  else
                      return a.freq < b.freq;
              });
}

void Huffman::build_tree()
{
    struct Compare
    {
        bool operator()(Node *a, Node *b)
        {
            // 1. Primary: ascending frequency
            if (a->freq != b->freq)
                return a->freq > b->freq;

            // 3. Tertiary: order of apparition (lower priority first)
            return a->priority > b->priority;
        }
    };

    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;

    for (auto &f : freq_table_)
        pq.push(new Node(f.freq, f.symbol, f.elem_no));

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *parent = new Node(left->freq + right->freq, '\0', 0);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    root_ = pq.top();
}

void Huffman::build_codes(Node *node, const std::string &prefix)
{
    if (!node)
        return;

    if (!node->left && !node->right)
    {
        codes_[node->symbol] = prefix;
        return;
    }

    build_codes(node->left, prefix + "0");
    build_codes(node->right, prefix + "1");
}