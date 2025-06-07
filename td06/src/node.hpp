#pragma once
#include <vector>

struct Node {
    int value;
    Node* left { nullptr };
    Node* right { nullptr };

    bool is_leaf() const;
    void insert(int value);
    int height() const;
    void delete_children();
    void display_infix() const;
    std::vector<Node const*> prefix() const;
    int min() const;
    int max() const;
};

Node* create_node(int value);

// UTILS
void pretty_print_left_right(Node const& node);
Node*& most_left(Node*& node);
bool remove(Node*& node, int value);
void delete_tree(Node* node);