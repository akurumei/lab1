#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm> // Для std::remove_if та std::transform
#include <cctype>    // Для std::isalpha та ::tolower

// Функція для перевірки, чи всі літери в слові унікальні
bool hasUniqueLetters(const std::string& word) {
    std::unordered_set<char> letters; 
    for (char c : word) {
        if (letters.count(c)) {
            return false; // Літера повторюється
        }
        letters.insert(c);
    }
    return true;
}

int main() {
    std::ifstream file("Test1.txt");
    if (!file) {
        std::cerr << "Не вдалося відкрити файл!" << std::endl;
        return 1;
    }

    std::unordered_set<std::string> uniqueWords;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;

        while (ss >> word) {
            // Видалення непотрібних символів
            word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return !std::isalpha(c); }), word.end());
            // Перетворення до нижнього регістру
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (word.length() <= 30 && hasUniqueLetters(word)) {
                uniqueWords.insert(word);
            }
        }
    }

    file.close();

    std::ofstream outFile("output.txt");
    if (!outFile) {
        std::cerr << "Не вдалося створити файл output.txt!" << std::endl;
        return 1;
    }

    for (const auto& word : uniqueWords) {
        outFile << word << std::endl;
    }

    outFile.close();

    return 0;
}
