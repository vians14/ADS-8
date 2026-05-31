// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>
#include <chrono>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    std::cout << "Алгоритмы и структуры данных (ADS-8)\n";
    std::cout << "Частотный анализ слов в романе 'Война и мир'\n";
    std::cout << "===============================================\n\n";
    
    BST<std::string> tree;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    const char* filename = "src/war_peace.txt";
    std::cout << "Чтение файла: " << filename << "\n";
    std::cout << "Пожалуйста, подождите, файл очень большой...\n\n";
    
    makeTree(tree, filename);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    
    std::cout << "Дерево успешно построено!\n";
    std::cout << "Глубина (высота) дерева: " << tree.depth() << "\n";
    std::cout << "Время построения: " << duration.count() << " секунд\n\n";
    
    printFreq(tree);
    
    std::cout << "\n=== Проверка поиска слов ===\n";
    std::string testWords[] = {"the", "war", "peace", "and", "tolstoy", "russia"};
    
    for (const std::string& word : testWords) {
        if (tree.search(word)) {
            std::cout << "Слово '" << word << "' найдено в дереве\n";
        } else {
            std::cout << "Слово '" << word << "' НЕ найдено в дереве\n";
        }
    }
    
    std::cout << "\nПрограмма завершена!\n";
    
    return 0;
}
