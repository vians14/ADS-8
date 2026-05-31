// Copyright 2021 NNTU-CS

#include  "bst.h"

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

bool isLatinLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

char toLowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    
    std::string currentWord;
    char ch;
    
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
            currentWord += toLowerCase(ch);
        } 
        else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
    }
    
    if (!currentWord.empty()) {
        tree.insert(currentWord);
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
    if (!outFile) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    
    for (const auto& node : nodes) {
        outFile << node.first << " " << node.second << std::endl;
        std::cout << node.first << " " << node.second << std::endl;
    }
    
    outFile.close();
}
