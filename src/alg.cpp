// Copyright 2021 NNTU-CS

#include  "bst.h"

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    std::string word;
    char c;
    
    while (file.get(c)) {
        // только латинские буквы A-Z a-z
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            // приводим к нижнему регистру
            if (c >= 'A' && c <= 'Z') {
                c = c + ('a' - 'A');
            }
            word += c;
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

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> nodes;
    tree.getAllNodes(nodes);
    
    std::sort(nodes.begin(), nodes.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    
    std::ofstream out("result/freq.txt");
    for (const auto& p : nodes) {
        out << p.first << " " << p.second << "\n";
        std::cout << p.first << " " << p.second << "\n";
    }
    out.close();
}
