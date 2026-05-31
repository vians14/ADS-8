// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

template<typename T>
class BST {
private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
        Node(const T& val) : data(val), count(1), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value < node->data) {
            insert(node->left, value);
        } else if (node->data < value) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }
    
    int getDepth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(getDepth(node->left), getDepth(node->right));
    }
    
    bool find(Node* node, const T& value) const {
        if (!node) return false;
        if (value < node->data) return find(node->left, value);
        if (node->data < value) return find(node->right, value);
        return true;
    }
    
    void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.push_back({node->data, node->count});
        collect(node->right, out);
    }
    
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    
    void insert(const T& value) { insert(root, value); }
    bool search(const T& value) const { return find(root, value); }
    int depth() const { return getDepth(root) - 1; }
    void getAllNodes(std::vector<std::pair<T, int>>& out) const { collect(root, out); }
};

#endif
