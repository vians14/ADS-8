// Copyright 2021 NNTU-CS

#include  "bst.h"

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <sstream>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: cannot open " << filename << std::endl;
        return;
    }
    
    std::string word;
    char ch;
    
    while (file.get(ch)) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + 32;
            }
            word += ch;
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
        std::cout << node.first << " " << node.second << std::endl;
    }
    
    outFile.close();
}
