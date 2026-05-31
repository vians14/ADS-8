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
        
        Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    Node* insert(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insert(node->left, value);
        } 
        else if (value > node->data) {
            node->right = insert(node->right, value);
        } 
        else {
            node->count++;
        }
        
        return node;
    }
    
    int depthHelper(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        
        int leftDepth = depthHelper(node->left);
        int rightDepth = depthHelper(node->right);
        
        if (leftDepth > rightDepth) {
            return leftDepth + 1;
        } else {
            return rightDepth + 1;
        }
    }
    
    Node* searchHelper(Node* node, const T& value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }
        
        if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }
    
    void clearHelper(Node* node) {
        if (node == nullptr) return;
        
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
    
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node == nullptr) return;
        
        collectNodes(node->left, nodes);
        nodes.push_back(std::make_pair(node->data, node->count));
        collectNodes(node->right, nodes);
    }
    
public:
    BST() : root(nullptr) {}
    
    ~BST() {
        clearHelper(root);
    }
    
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    bool search(const T& value) const {
        return searchHelper(root, value) != nullptr;
    }
    
    int depth() const {
        return depthHelper(root);
    }
    
    void getAllNodes(std::vector<std::pair<T, int>>& nodes) const {
        collectNodes(root, nodes);
    }
};

#endif
