#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <locale>

using namespace std;

struct HuffmanNode {
    char symbol;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    // Конструктор для листовых узлов
    HuffmanNode(char symbol, int frequency) {
        this->symbol = symbol;
        this->frequency = frequency;
        left = right = nullptr;
    }

    // Конструктор для внутренних узлов, объединяющий два поддерева
    HuffmanNode(int frequency, HuffmanNode* left, HuffmanNode* right) {
        this->symbol = '\0'; 
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

// Функция для построения кодов символов
void buildHuffmanCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->symbol] = str;
    }
    buildHuffmanCodes(root->left, str + "0", huffmanCode);
    buildHuffmanCodes(root->right, str + "1", huffmanCode);
}

// Функция для освобождения памяти
void freeTree(HuffmanNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Основная функция для кодирования
void huffmanEncode(const string& text) {
    unordered_map<char, int> frequency;
    for (char ch : text) {
        frequency[ch]++;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : frequency) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        int sum = left->frequency + right->frequency;
        pq.push(new HuffmanNode(sum, left, right));
    }

    HuffmanNode* root = pq.top();

    unordered_map<char, string> huffmanCode;
    buildHuffmanCodes(root, "", huffmanCode);

    // Вывод кодов и закодированной строки
    cout << "Символы с кодами Хаффмана:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    cout << "\nИсходная строка: " << text << "\nЗакодированная строка: ";
    string encodedString;
    int encodedSize = 0;
    for (char ch : text) {
        encodedString += huffmanCode[ch];
        encodedSize += huffmanCode[ch].length();
    }
    cout << encodedString << endl;

    // Расчет процента сжатия
    int originalSize = text.length() * 8;
    double compressionRatio = (1 - (double)encodedSize / originalSize) * 100;

    cout << "Исходный размер (в битах): " << originalSize << "\n";
    cout << "Закодированный размер (в битах): " << encodedSize << "\n";
    cout << "Процент сжатия: " << compressionRatio << "%\n";

    freeTree(root);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string text = "Лазаренко Сергей Александрович";
    huffmanEncode(text);

    return 0;
}