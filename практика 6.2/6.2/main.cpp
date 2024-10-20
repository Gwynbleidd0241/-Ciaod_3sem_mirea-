//  main.cpp
//  6.2
//
//  Created by Сергей Лазаренко on 07.10.2024.
//
//№1
//#include <iostream>
//#include <sstream>
//#include <vector>
//#include <string>
//
//std::vector<int> splitIntoIntegers(const std::string& sentence) { // Функция для разделения строки на числа
//    
//    std::vector<int> numbers;
//    std::istringstream stream(sentence);
//    std::string word;
//    
//    while (stream >> word) {
//        try {
//            numbers.push_back(std::stoi(word));
//        } catch (std::invalid_argument&) {
//            std::cerr << "Слово не является целым числом: " << word << std::endl;
//        }
//    }
//
//    return numbers;
//}
//
//int main() {
//    std::string sentence = "12 34 56 78 81 96";
//    std::vector<int> numbers = splitIntoIntegers(sentence);
//
//    std::cout << "Массив чисел: ";
//    for (int num : numbers) {
//        std::cout << num << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}

//№2
#include <iostream>
#include <vector>
#include <string>

bool isPrefix(const std::string& pattern, int p);
int suffixLength(const std::string& pattern, int p);

std::vector<int> buildGoodSuffixTable(const std::string& pattern) { //Функция для построения таблицы сдвигов хорошего суффикса

    int m = pattern.size();
    std::vector<int> goodSuffix(m, m);
    int lastPrefixPosition = m;

    for (int i = m - 1; i >= 0; --i) {
        if (isPrefix(pattern, i + 1)) {
            lastPrefixPosition = i + 1;
        }
        goodSuffix[m - 1 - i] = lastPrefixPosition - i + m - 1;
    }

    for (int i = 0; i < m - 1; ++i) {
        int slen = suffixLength(pattern, i);
        goodSuffix[slen] = m - 1 - i + slen;
    }

    return goodSuffix;
}

// Проверка, является ли подстрока суффиксом строки
bool isPrefix(const std::string& pattern, int p) {
    int m = pattern.size();
    int j = 0;
    for (int i = p; i < m; ++i) {
        if (pattern[i] != pattern[j]) {
            return false;
        }
        ++j;
    }
    return true;
}

// Длина максимального суффикса подстроки, заканчивающегося на i
int suffixLength(const std::string& pattern, int p) {
    int m = pattern.size();
    int length = 0;
    int i = p;
    int j = m - 1;
    while (i >= 0 && pattern[i] == pattern[j]) {
        ++length;
        --i;
        --j;
    }
    return length;
}

// Основной алгоритм Бойера-Мура с эвристикой хорошего суффикса
std::vector<int> boyerMooreSearch(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) {
        return {};
    }

    std::vector<int> goodSuffix = buildGoodSuffixTable(pattern);
    std::vector<int> occurrences;
    int i = 0;

    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            --j;
        }
        if (j < 0) {
            occurrences.push_back(i);
            i += goodSuffix[0];
        } else {
            i += goodSuffix[m - 1 - j];
        }
    }

    return occurrences;
}

int main() {
    std::string text = "ababcababcabc";
    std::string pattern = "abc";
    std::vector<int> result = boyerMooreSearch(text, pattern);

    std::cout << "Вхождения подстроки: ";
    for (int pos : result) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    return 0;
}
