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
        if (node == nullptr) {
            node = new Node(value);
            return;
        }
        
        if (value < node->data) {
            insert(node->left, value);
        }
        else if (value > node->data) {
            insert(node->right, value);
        }
        else {
            node->count++;
        }
    }
    
    int getDepth(Node* node) const {
        if (node == nullptr) return 0;
        int left = getDepth(node->left);
        int right = getDepth(node->right);
        return 1 + (left > right ? left : right);
    }
    
    bool searchNode(Node* node, const T& value) const {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }
    
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (node == nullptr) return;
        collectNodes(node->left, vec);
        vec.push_back({node->data, node->count});
        collectNodes(node->right, vec);
    }
    
    void clearTree(Node* node) {
        if (node == nullptr) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
    
public:
    BST() : root(nullptr) {}
    
    ~BST() {
        clearTree(root);
    }
    
    void insert(const T& value) {
        insert(root, value);
    }
    
    bool search(const T& value) const {
        return searchNode(root, value);
    }
    
    int depth() const {
        return getDepth(root) - 1;
    }
    
    void getAllNodes(std::vector<std::pair<T, int>>& nodes) const {
        collectNodes(root, nodes);
    }
};

#endif
