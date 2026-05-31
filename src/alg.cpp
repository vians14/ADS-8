// Copyright 2021 NNTU-CS

#include  "bst.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    std::map<std::string, int> freq;
    std::string word;
    char c;
    
    while (file.get(c)) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
            word += c;
        } else if (!word.empty()) {
            freq[word]++;
            word.clear();
        }
    }
    if (!word.empty()) freq[word]++;
    
    file.close();
    
    for (auto& p : freq) {
        for (int i = 0; i < p.second; i++) {
            tree.insert(p.first);
        }
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> nodes;
    tree.getAllNodes(nodes);
    
    std::sort(nodes.begin(), nodes.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
    
    std::ofstream out("result/freq.txt");
    for (const auto& p : nodes) {
        out << p.first << " " << p.second << "\n";
    }
    out.close();
}
