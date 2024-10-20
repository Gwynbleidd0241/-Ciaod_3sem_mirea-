////  main.cpp
////  5.2
////  Created by Сергей Лазаренко on 21.09.2024.
//// №1
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <random>
//#include <set>
//#include <cstring>
//
//using namespace std;
//
//// Структура записи
//struct Record {
//    int cardNumber;          // Номер читательского билета
//    char name[50];           // ФИО
//    char address[100];       // Адрес
//};
//
//// Функция генерации случайных данных
//void generateData(int recordCount, vector<Record>& records) {
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> distr(10000, 99999); // Генерация пятизначных чисел
//    set<int> uniqueNumbers;
//
//    // Массивы возможных ФИО и адресов
//    vector<string> names = { "Ivan Ivanov", "Petr Petrov", "Sergey Sidorov", "Anna Smirnova", "Olga Pavlova" };
//    vector<string> addresses = { "Moscow, Lenin St.", "Saint Petersburg, Nevskiy Ave.", "Kazan, Tverskaya St.", "Novosibirsk, Karl Marx St.", "Yekaterinburg, Gagarina Ave." };
//
//    while (uniqueNumbers.size() < recordCount) {
//        uniqueNumbers.insert(distr(gen)); // Уникальные номера
//    }
//
//    auto it = uniqueNumbers.begin();
//    for (int i = 0; i < recordCount; ++i) {
//        Record rec;
//        rec.cardNumber = *it++;
//        strncpy(rec.name, names[i % names.size()].c_str(), sizeof(rec.name) - 1);
//        strncpy(rec.address, addresses[i % addresses.size()].c_str(), sizeof(rec.address) - 1);
//        rec.name[sizeof(rec.name) - 1] = '\0';
//        rec.address[sizeof(rec.address) - 1] = '\0';
//        records.push_back(rec);
//    }
//}
//
//// Функция записи данных в текстовый файл
//void writeTextFile(const string& filename, const vector<Record>& records) {
//    ofstream outFile(filename);
//    if (!outFile) {
//        cerr << "Ошибка при открытии файла " << filename << endl;
//        return;
//    }
//
//    for (const auto& rec : records) {
//        outFile << rec.cardNumber << "\t" << rec.name << "\t" << rec.address << endl;
//    }
//    outFile.close();
//}
//
//// Функция конвертации текстового файла в двоичный
//void convertToBinary(const string& textFilename, const string& binaryFilename) {
//    ifstream inFile(textFilename);
//    ofstream outFile(binaryFilename, ios::binary);
//
//    if (!inFile || !outFile) {
//        cerr << "Ошибка при открытии файлов" << endl;
//        return;
//    }
//
//    Record rec;
//    while (inFile >> rec.cardNumber) {
//        inFile.ignore(); // Пропускаем табуляцию
//        inFile.getline(rec.name, sizeof(rec.name), '\t');
//        inFile.getline(rec.address, sizeof(rec.address));
//        outFile.write(reinterpret_cast<char*>(&rec), sizeof(Record));
//    }
//
//    inFile.close();
//    outFile.close();
//}
//
//// Функция чтения данных из двоичного файла
//void readBinaryFile(const string& binaryFilename) {
//    ifstream inFile(binaryFilename, ios::binary);
//    if (!inFile) {
//        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
//        return;
//    }
//
//    Record rec;
//    while (inFile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
//        cout << "Номер читательского билета: " << rec.cardNumber << "\n"
//             << "ФИО: " << rec.name << "\n"
//             << "Адрес: " << rec.address << "\n"
//             << "--------------------------" << endl;
//    }
//
//    inFile.close();
//}
//
//int main() {
//    const int recordCount = 100;
//    vector<Record> records;
//
//    // Генерация данных
//    generateData(recordCount, records);
//
//    // Запись данных в текстовый файл
//    const string textFilename = "records.txt";
//    writeTextFile(textFilename, records);
//
//    // Конвертация текстового файла в двоичный
//    const string binaryFilename = "records.bin";
//    convertToBinary(textFilename, binaryFilename);
//
//    // Чтение данных из двоичного файла
//    cout << "Чтение данных из двоичного файла:" << endl;
//    readBinaryFile(binaryFilename);
//
//    return 0;
//}
// №2
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <random>
//#include <set>
//#include <cstring>
//#include <chrono>
//#include <stdexcept>
//
//using namespace std;
//
//struct Record {
//    int cardNumber;
//    char name[50];
//    char address[100];
//};
//
//void generateData(int recordCount, vector<Record>& records) {
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> distr(10000, 99999);
//    set<int> uniqueNumbers;
//
//    vector<string> names = { "Ivan Ivanov", "Petr Petrov", "Sergey Sidorov", "Anna Smirnova", "Olga Pavlova" };
//    vector<string> addresses = { "Moscow, Lenin St.", "Saint Petersburg, Nevskiy Ave.", "Kazan, Tverskaya St.", "Novosibirsk, Karl Marx St.", "Yekaterinburg, Gagarina Ave." };
//
//    // Генерация уникальных номеров
//    while (uniqueNumbers.size() < recordCount) {
//        uniqueNumbers.insert(distr(gen));
//    }
//
//    auto it = uniqueNumbers.begin();
//    for (int i = 0; i < recordCount; ++i) {
//        Record rec;
//        rec.cardNumber = *it++;
//        strncpy(rec.name, names[i % names.size()].c_str(), sizeof(rec.name) - 1);
//        strncpy(rec.address, addresses[i % addresses.size()].c_str(), sizeof(rec.address) - 1);
//        rec.name[sizeof(rec.name) - 1] = '\0';
//        rec.address[sizeof(rec.address) - 1] = '\0';
//        records.push_back(rec);
//    }
//}
//
//// Функция записи данных в текстовый файл
//void writeTextFile(const string& filename, const vector<Record>& records) {
//    ofstream outFile(filename);
//    if (!outFile) {
//        cerr << "Ошибка при открытии файла " << filename << endl;
//        return;
//    }
//
//    for (const auto& rec : records) {
//        outFile << rec.cardNumber << "\t" << rec.name << "\t" << rec.address << endl;
//    }
//    outFile.close();
//}
//
//// Функция конвертации текстового файла в двоичный
//void convertToBinary(const string& textFilename, const string& binaryFilename) {
//    ifstream inFile(textFilename);
//    ofstream outFile(binaryFilename, ios::binary);
//
//    if (!inFile || !outFile) {
//        cerr << "Ошибка при открытии файлов" << endl;
//        return;
//    }
//
//    Record rec;
//    while (inFile >> rec.cardNumber) {
//        inFile.ignore();
//        inFile.getline(rec.name, sizeof(rec.name), '\t');
//        inFile.getline(rec.address, sizeof(rec.address));
//        outFile.write(reinterpret_cast<char*>(&rec), sizeof(Record));
//    }
//
//    inFile.close();
//    outFile.close();
//}
//
//Record linearSearch(const string& binaryFilename, int key) {
//    ifstream inFile(binaryFilename, ios::binary);
//    if (!inFile) {
//        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
//        throw runtime_error("File not found");
//    }
//
//    Record rec;
//    while (inFile.read(reinterpret_cast<char*>(&rec), sizeof(Record))) {
//        if (rec.cardNumber == key) {
//            inFile.close();
//            return rec;
//        }
//    }
//
//    inFile.close();
//    throw runtime_error("Запись не найдена");
//}
//
//long long testSearchTime(const string& binaryFilename, int key) {
//    auto start = chrono::high_resolution_clock::now(); // Начало отсчета времени
//    try {
//        linearSearch(binaryFilename, key);
//    } catch (...) {
//        // Игнорируем ошибки, так как нас интересует только время
//    }
//    auto end = chrono::high_resolution_clock::now(); // Конец отсчета времени
//    return chrono::duration_cast<chrono::microseconds>(end - start).count();
//}
//
//// Основной код программы
//int main() {
//    const int recordCounts[] = {100, 1000, 10000}; // Различные размеры файлов
//    vector<long long> searchTimes; // Времена выполнения поиска
//
//    cout << "Размер файла | Время поиска (мкс)" << endl;
//    cout << "--------------|---------------------" << endl;
//
//    for (int count : recordCounts) {
//        vector<Record> records;
//        generateData(count, records); // Генерация данных
//        writeTextFile("records.txt", records); // Запись в текстовый файл
//        convertToBinary("records.txt", "records.bin"); // Конвертация в двоичный файл
//
//        // Вызов функции для замера времени поиска
//        long long duration = testSearchTime("records.bin", records[0].cardNumber);
//        searchTimes.push_back(duration);
//        
//        cout << count << "          | " << duration << endl;
//    }
//
//    return 0;
//}
//№3
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <set>
#include <chrono>

using namespace std;

// Структура записи
struct Record {
    int cardNumber;
    char name[50];
    char address[100];
};

// Функция для генерации данных
void generateData(int recordCount, vector<Record>& records) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(10000, 99999);
    set<int> uniqueNumbers;

    vector<string> names = { "Ivan Ivanov", "Petr Petrov", "Sergey Sidorov", "Anna Smirnova", "Olga Pavlova" };
    vector<string> addresses = { "Moscow, Lenin St.", "Saint Petersburg, Nevsky Ave.", "Kazan, Tverskaya St.", "Novosibirsk, Karl Marx St.", "Yekaterinburg, Gagarina Ave." };

    while (uniqueNumbers.size() < recordCount) {
        uniqueNumbers.insert(dist(gen));
    }

    auto it = uniqueNumbers.begin();
    for (int i = 0; i < recordCount; ++i) {
        Record rec;
        rec.cardNumber = *it++;
        strncpy(rec.name, names[i % names.size()].c_str(), sizeof(rec.name) - 1);
        rec.name[sizeof(rec.name) - 1] = '\0';
        strncpy(rec.address, addresses[i % addresses.size()].c_str(), sizeof(rec.address) - 1);
        rec.address[sizeof(rec.address) - 1] = '\0';
        records.push_back(rec);
    }
}

// Функция для записи данных в текстовый файл
void writeTextFile(const string& filename, const vector<Record>& records) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка при открытии файла " << filename << endl;
        return;
    }

    for (const auto& rec : records) {
        outFile << rec.cardNumber << "\t" << rec.name << "\t" << rec.address << endl;
    }
    outFile.close();
}

// Функция конвертации текстового файла в бинарный
void convertToBinary(const string& textFilename, const string& binaryFilename) {
    ifstream inFile(textFilename);
    ofstream outFile(binaryFilename, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Ошибка при открытии файлов" << endl;
        return;
    }

    Record rec;
    while (inFile >> rec.cardNumber) {
        inFile.ignore();
        inFile.getline(rec.name, sizeof(rec.name), '\t');
        inFile.getline(rec.address, sizeof(rec.address));
        outFile.write(reinterpret_cast<char*>(&rec), sizeof(Record));
    }
}

// Функция для поиска записи с использованием бинарного поиска
bool binarySearchInFile(const string& binaryFilename, int searchKey, Record& foundRecord) {
    ifstream inFile(binaryFilename, ios::binary);
    
    if (!inFile) {
        cerr << "Ошибка при открытии файла " << binaryFilename << endl;
        return false;
    }

    inFile.seekg(0, ios::end);
    size_t fileSize = inFile.tellg();
    size_t recordCount = fileSize / sizeof(Record);

    size_t low = 0;
    size_t high = recordCount - 1;
    
    while (low <= high) {
        size_t mid = (low + high) / 2;
        inFile.seekg(mid * sizeof(Record));
        inFile.read(reinterpret_cast<char*>(&foundRecord), sizeof(Record));

        if (foundRecord.cardNumber == searchKey) {
            return true;
        } else if (foundRecord.cardNumber < searchKey) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

// Основная функция программы
int main() {
    vector<Record> records;
    generateData(10000, records);

    string textFilename = "records.txt";
    string binaryFilename = "records.bin";

    writeTextFile(textFilename, records);
    convertToBinary(textFilename, binaryFilename);

    int searchKey = records[0].cardNumber;
    Record foundRecord;

    auto start = chrono::high_resolution_clock::now();
    bool found = binarySearchInFile(binaryFilename, searchKey, foundRecord);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    if (found) {
        cout << "Запись найдена: " << foundRecord.cardNumber << " " << foundRecord.name << " " << foundRecord.address << endl;
    } else {
        cout << "Запись не найдена." << endl;
    }

    cout << "Время поиска: " << duration << " мкс" << endl;

    return 0;
}
