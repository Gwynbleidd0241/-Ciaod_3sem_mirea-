#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Symbol {
    char character;
    int frequency;
    string code;

    Symbol(char c, int freq, string cde) : character(c), frequency(freq), code(cde) {}
};

// Функция для сортировки символов по частотам
bool compareByFrequency(const Symbol& a, const Symbol& b) {
    return a.frequency > b.frequency;
}

// Рекурсивная функция для построения кодов Шеннона-Фано
void shannonFanoCoding(vector<Symbol>& symbols, int start, int end) {
    if (start >= end) return;
    
    int totalFrequency = 0;
    for (int i = start; i <= end; i++)
        totalFrequency += symbols[i].frequency;

    int splitPoint = start;
    int cumulativeFrequency = 0;
    for (int i = start; i <= end; i++) {
        cumulativeFrequency += symbols[i].frequency;
        if (cumulativeFrequency >= totalFrequency / 2) {
            splitPoint = i;
            break;
        }
    }

    // Разделяем и добавляем соответствующие префиксы
    for (int i = start; i <= splitPoint; i++)
        symbols[i].code += "0";
    for (int i = splitPoint + 1; i <= end; i++)
        symbols[i].code += "1";

    shannonFanoCoding(symbols, start, splitPoint);
    shannonFanoCoding(symbols, splitPoint + 1, end);
}

// Функция для сжатия текста
void compressText(const string& inputFile, const string& outputFile, unordered_map<char, string>& encodingMap) {
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    unordered_map<char, int> frequencyMap;
    string text((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    // Подсчитываем частоту каждого символа
    for (char ch : text)
        frequencyMap[ch]++;

    vector<Symbol> symbols;
    for (auto& pair : frequencyMap)
        symbols.push_back(Symbol(pair.first, pair.second, ""));  // Исправлена инициализация

    // Сортируем символы по частоте
    sort(symbols.begin(), symbols.end(), compareByFrequency);

    // Строим кодировку Шеннона-Фано
    shannonFanoCoding(symbols, 0, symbols.size() - 1);

    // Заполняем карту кодирования
    for (auto& symbol : symbols)
        encodingMap[symbol.character] = symbol.code;

    // Сжимаем текст
    ofstream outFile(outputFile, ios::binary);
    string compressedText;
    for (char ch : text)
        compressedText += encodingMap[ch];

    outFile << compressedText;
    outFile.close();

    // Вычисляем размеры в битах
    int originalSize = text.size() * 8; // 8 бит на символ
    int compressedSize = 0;
    for (char ch : text) {
        compressedSize += encodingMap[ch].size(); // Добавляем длину кода для каждого символа
    }

    // Выводим процент сжатия
    if (originalSize != 0) {
        cout << "Процент сжатия: " << (100.0 - (100.0 * compressedSize / originalSize)) << "%" << endl;
    } else {
        cout << "Ошибка: исходный текст пустой." << endl;
    }
}

// Функция для декодирования текста
void decompressText(const string& inputFile, const string& outputFile, unordered_map<char, string>& encodingMap) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Ошибка открытия файла." << endl;
        return;
    }

    unordered_map<string, char> decodingMap;
    for (const auto& pair : encodingMap) {
        decodingMap[pair.second] = pair.first;
    }

    string compressedText((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    // Декодируем текст
    string codeBuffer;
    string decompressedText;
    for (char bit : compressedText) {
        codeBuffer += bit;
        if (decodingMap.find(codeBuffer) != decodingMap.end()) {
            decompressedText += decodingMap[codeBuffer];
            codeBuffer.clear();
        }
    }

    // Записываем декодированный текст в файл
    ofstream outFile(outputFile);
    outFile << decompressedText;
    outFile.close();
}

int main() {
    // Устанавливаем локаль для корректной работы с текстом на русском и других символах
    setlocale(LC_ALL, "en_US.UTF-8");

    // Карта для хранения кодов символов
    unordered_map<char, string> encodingMap;

    // Пример работы с сжатием и распаковкой текста
    compressText("input.txt", "output.txt", encodingMap);
    decompressText("output.txt", "output2.txt", encodingMap);

    return 0;
}

