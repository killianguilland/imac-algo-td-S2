#include "node.hpp"
#include <string>
#include <iostream>



Node* create_node(int value) {
    return new Node{value, nullptr, nullptr};
}

bool Node::is_leaf() const {
    return !left && !right;
}

void Node::insert(int value) {
    if (value < this->value) {
        if (left) {
            left->insert(value);
        } else {
            left = create_node(value);
        }
    } else {
        if (right) {
            right->insert(value);
        } else {
            right = create_node(value);
        }
    }
}

int Node::height() const {
    int left_height = left ? left->height() : 0;
    int right_height = right ? right->height() : 0;
    return 1 + std::max(left_height, right_height);
}

void Node::delete_children() {
    if (left) {
        left->delete_children();
        delete left;
        left = nullptr;
    }
    if (right) {
        right->delete_children();
        delete right;
        right = nullptr;
    }
}

void Node::display_infix() const {
    if (left) {
        left->display_infix();
    }
    std::cout << value << " ";
    if (right) {
        right->display_infix();
    }
}

std::vector<Node const*> Node::prefix() const {
    std::vector<Node const*> nodes;
    nodes.push_back(this);
    if (left) {
        auto left_nodes = left->prefix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    if (right) {
        auto right_nodes = right->prefix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    return nodes;
}

int Node::min() const {
    const Node* current = this;
    while (current->left) {
        current = current->left;
    }
    return current->value;
}

int Node::max() const {
    const Node* current = this;
    while (current->right) {
        current = current->right;
    }
    return current->value;
}

// UTILS

void pretty_print_left_right(Node const& node, std::string const& prefix, bool is_left) {
    if (node.right) {
        pretty_print_left_right(*node.right, prefix + (is_left ? "|   " : "    "), false);
    }
    std::cout << prefix << (is_left ? "+-- " : "+-- ") << node.value << std::endl;
    if (node.left) {
        pretty_print_left_right(*node.left, prefix + (is_left ? "    " : "|   "), true);
    }
}

void pretty_print_left_right(Node const& node) {
    pretty_print_left_right(node, "", true);
}

Node*& most_left(Node*& node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }
    return most_left(node->left);
}

bool remove(Node*& node, int value) {
    if (!node) return false;
    if (value < node->value) {
        return remove(node->left, value);
    } else if (value > node->value) {
        return remove(node->right, value);
    } else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (!node->right) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node*& minNode = most_left(node->right);
            node->value = minNode->value;
            remove(minNode, minNode->value);
        }
        return true;
    }
}

void delete_tree(Node* node) {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}