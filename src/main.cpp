// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  std::cout << tree.depth() << "\n";
  printFreq(tree);
  return 0;
}
