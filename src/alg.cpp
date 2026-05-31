// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>


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
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
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
        std::cerr << "Ошибка: не удалось создать файл result/freq.txt" << std::endl;
        return;
    }
    
    std::cout << "\n========== ЧАСТОТНЫЙ АНАЛИЗ СЛОВ ==========\n";
    std::cout << "Всего уникальных слов: " << nodes.size() << "\n\n";
    std::cout << "Слово\t\t\tЧастота\n";
    std::cout << "----------------------------------------\n";
    
    outFile << "Частотный анализ слов из романа 'Война и мир'\n";
    outFile << "Всего уникальных слов: " << nodes.size() << "\n\n";
    outFile << "Слово\t\t\tЧастота\n";
    outFile << "----------------------------------------\n";
    
    int count = 0;
    for (const auto& node : nodes) {
        count++;
        
        std::string word = node.first;
        int freq = node.second;
        
        std::cout << word;
        for (int i = word.length(); i < 20; i++) std::cout << ' ';
        std::cout << "\t" << freq << "\n";
        
        outFile << word;
        for (int i = word.length(); i < 20; i++) outFile << ' ';
        outFile << "\t" << freq << "\n";
        
        if (count >= 50) {
            std::cout << "\n... и еще " << nodes.size() - 50 << " слов\n";
            break;
        }
    }
    
    if (count < nodes.size()) {
        for (size_t i = count; i < nodes.size(); i++) {
            std::string word = nodes[i].first;
            int freq = nodes[i].second;
            outFile << word;
            for (int i = word.length(); i < 20; i++) outFile << ' ';
            outFile << "\t" << freq << "\n";
        }
    }
    
    std::cout << "\nПолный список сохранен в файл result/freq.txt\n";
    std::cout << "============================================\n";
    
    outFile.close();
}
