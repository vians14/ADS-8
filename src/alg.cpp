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
    
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file" << std::endl;
        return;
    }
    
    std::string word;
    char c;
    
    while (file.get(c)) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (c >= 'A' && c <= 'Z') {
                c = c + 32;
            }
            word.push_back(c);
        } else {
            if (word.length() > 0) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    
    if (word.length() > 0) {
        tree.insert(word);
    }
    
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> nodes;
    tree.getAllNodes(nodes);
    
    std::sort(nodes.begin(), nodes.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });
    
    std::ofstream outFile("result/freq.txt");
    
    for (const auto& node : nodes) {
        outFile << node.first << " " << node.second << std::endl;
    }
    
    outFile.close();
}
