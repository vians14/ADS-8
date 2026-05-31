#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

template<typename T>
class BST {
 public:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& val) : data(val), count(1), left(nullptr), right(nullptr) {}
  };

 private:
  Node* root;

  void insert(Node*& node, const T& value) {
    if (node == nullptr) {
      node = new Node(value);
      return;
    }
    if (value < node->data) {
      insert(node->left, value);
    } else if (value > node->data) {
      insert(node->right, value);
    } else {
      node->count++;
    }
  }

  int getDepth(Node* node) const {
    if (node == nullptr) return -1;
    return 1 + std::max(getDepth(node->left), getDepth(node->right));
  }

  int find(Node* node, const T& value) const {
    if (node == nullptr) return 0;
    if (value == node->data) return node->count;
    if (value < node->data) return find(node->left, value);
    return find(node->right, value);
  }

  void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (node == nullptr) return;
    collect(node->left, out);
    out.push_back({node->data, node->count});
    collect(node->right, out);
  }

  void clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(const T& value) { insert(root, value); }
  int search(const T& value) const { return find(root, value); }
  int depth() const { return getDepth(root); }
  void getAllNodes(std::vector<std::pair<T, int>>& out) const { collect(root, out); }
  Node* getRoot() const { return root; }
};

#endif  // INCLUDE_BST_H_
