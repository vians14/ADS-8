#include "bst.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;

  std::string word;
  int ch;

  while ((ch = file.get()) != EOF) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

namespace {
struct PairVec {
  std::vector<std::pair<std::string, int>> data;
};

void collectInorder(BST<std::string>::Node* node, PairVec& pv) {
  if (!node) return;
  collectInorder(node->left, pv);
  pv.data.push_back({node->data, node->count});
  collectInorder(node->right, pv);
}
}  // namespace

void printFreq(BST<std::string>& tree) {
  PairVec pv;
  collectInorder(tree.getRoot(), pv);

  std::sort(pv.data.begin(), pv.data.end(),
    [](const auto& a, const auto& b) { return a.second > b.second; });

  std::ofstream out("result/freq.txt");
  for (const auto& p : pv.data) {
    out << p.first << " " << p.second << "\n";
  }
  out.close();
}
