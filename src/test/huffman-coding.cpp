#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <queue>

#define NULL_CHAR '\0'
#define NULL_LL 0

typedef long long int ll;

using namespace std;

struct FreqNode
{
    ll freq;
    char symbol;
    int elem_no;
};

class Node
{
public:
    // data of node is the frequency of each symbol
    ll freq_node;
    char char_node;
    ll priority;
    // pointer to the left child
    Node *left;
    // pointer to the right child
    Node *right;
    // initializer
    Node(ll f, char c, ll p)
    {
        freq_node = f;
        char_node = c;
        priority = p,
        left = nullptr;
        right = nullptr;
    }
};

class CompareNode
{
public:
    bool operator()(Node *a, Node *b)
    {
        // 1. Primary: ascending frequency
        if (a->freq_node != b->freq_node)
            return a->freq_node > b->freq_node;

        // 3. Tertiary: order of apparition (lower priority first)
        return a->priority > b->priority;
    }
};

void build_frequency_table(vector<FreqNode> &freq_table, string &s)
{
    set<char> seen_chars;
    unordered_map<char, int> idx_tracker;
    int curr_idx = 0;
    for (auto c : s)
    {
        if (seen_chars.find(c) != seen_chars.end())
        { // symbol has already been found
            int idx = idx_tracker[c];
            freq_table[idx].freq++;
        }
        else
        { // new symbol discovered -> add to set
            seen_chars.insert(c);
            // assign idx to symbol
            idx_tracker[c] = curr_idx;
            // add symbol to frequency table
            FreqNode node = {1, c, curr_idx};
            freq_table.push_back(node);
            // create next idx
            curr_idx++;
        }
    }
}

bool compare_freq_nodes(const FreqNode &a, const FreqNode &b)
{
    if (a.freq == b.freq)
    {
        return a.elem_no < b.elem_no;
    }
    else
        return a.freq < b.freq;
}

void print_freq_table(vector<FreqNode> &freq_table)
{
    for (auto node : freq_table)
    {
        cout << node.symbol << ": " << node.freq << "\n";
    }
}

void build_forest_roots(priority_queue<Node *, vector<Node *>, CompareNode> &min_heap, vector<FreqNode> &freq_table)
{
    for (auto f : freq_table)
    {
        Node *n = new Node(f.freq, f.symbol, f.elem_no); // create root with symbol and frequency
        min_heap.push(n);
    }
}

void huffman_tree(priority_queue<Node *, vector<Node *>, CompareNode> &min_heap)
{
    while (min_heap.size() >= 2)
    { // as long as there are two nodes in the min heap
        // left child
        Node *left_child = min_heap.top();
        min_heap.pop();

        // right child
        Node *right_child = min_heap.top();
        min_heap.pop();

        // join the first two nodes with a parent root
        ll sum_freq = left_child->freq_node + right_child->freq_node;
        Node *root = new Node(sum_freq, NULL_CHAR, NULL_LL);
        root->left = left_child;
        root->right = right_child;

        // add new tree to min heap
        min_heap.push(root);
    }
}

void dfs(Node *curr_node, unordered_map<char, string> &codes, string bin_code)
{
    // current node is a null pointer
    if (curr_node == nullptr)
        return;

    // current node is leaf
    if (curr_node->left == nullptr && curr_node->right == nullptr)
    {
        codes[curr_node->char_node] = bin_code;
        cout << curr_node->char_node << ": " << bin_code << "\n";
        return;
    }

    // dfs on left child
    dfs(curr_node->left, codes, bin_code + "0");

    // dfs on right child
    dfs(curr_node->right, codes, bin_code + "1");
}

void decode(Node *root, string &coded_s, string &result)
{
    Node *curr_node = root;
    for (auto bit : coded_s)
    {
        if (bit == '0')
        { // go left
            curr_node = curr_node->left;
        }
        else if (bit == '1')
        { // go right
            curr_node = curr_node->right;
        }
        // if leaf is reached
        if (!curr_node->left && !curr_node->right)
        {
            result += curr_node->char_node;
            curr_node = root;
        }
    }
}

void print_codes(unordered_map<char, string> &codes)
{
    for (auto c : codes)
    {
        cout << c.first << ": " << c.second << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;

    getline(cin, s);

    cout << "Length of string: " << s.size() << "\n";

    // frequency table
    vector<FreqNode> freq_table;

    // sort symbols by frequency and order of aparition in ascending order
    build_frequency_table(freq_table, s);
    sort(freq_table.begin(), freq_table.end(), compare_freq_nodes);

    // print frequency table
    print_freq_table(freq_table);

    // create a node for each symbol and add each one to min heap
    priority_queue<Node *, vector<Node *>, CompareNode> min_heap;
    build_forest_roots(min_heap, freq_table);

    // construct tree with nodes in min heap
    huffman_tree(min_heap);

    // assign binary code to each symbol
    unordered_map<char, string> codes;

    // Huffman tree
    Node *tree = min_heap.top();
    dfs(tree, codes, "");

    // print codes
    // print_codes(codes);

    // code string
    string coded_s = "";
    for (int i = 0; i < s.size(); i++)
    {
        coded_s += codes[s[i]];
    }
    cout << coded_s << "\n";

    // decode string
    string result = "";
    decode(tree, coded_s, result);
    cout << "Result: " << result;

    return 0;
}