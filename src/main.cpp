#include "bst.h"

#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  std::cout << tree.depth() << "\n";
  printFreq(tree);
  return 0;
}
