//
//  hash.cpp
//  6.1
//
//  Created by Сергей Лазаренко on 30.09.2024.
//
#include "hash.hpp"

string Data_Record::string_rep() {
    return "[Номер счета: " + to_string(account_number) + ", ФИО: " + full_name + ", Адрес: " + address + "]";
}

Hash_Table::Hash_Table(int table_size) : size(table_size), num_of_elements(0) {
    table = new Data_Record *[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

Hash_Table::~Hash_Table() {
    for (int i = 0; i < size; i++) {
        Data_Record *current = table[i];
        while (current != nullptr) {
            Data_Record *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

int Hash_Table::hash_function(int account_number) const {
    return account_number % size;
}

void Hash_Table::rehash() {
    cout << "Перехеширование: увеличиваем размер таблицы до " << size * 2 << endl;
    int old_size = size;
    size *= 2;
    Data_Record **new_table = new Data_Record *[size];
    for (int i = 0; i < size; i++) {
        new_table[i] = nullptr;
    }

    for (int i = 0; i < old_size; i++) {
        Data_Record *current = table[i];
        while (current != nullptr) {
            Data_Record *next_record = current->next;
            int new_index = hash_function(current->account_number);
            current->next = new_table[new_index];
            new_table[new_index] = current;
            current = next_record;
        }
    }

    delete[] table;
    table = new_table;
}

void Hash_Table::insert(Data_Record *new_record) {
    int index = hash_function(new_record->account_number);
    new_record->next = table[index];
    table[index] = new_record;
    num_of_elements++;
    if (static_cast<float>(num_of_elements) / size > load_factor_threshold) {
        rehash();
    }
}

Data_Record *Hash_Table::search(int account_number) {
    int index = hash_function(account_number);
    Data_Record *current = table[index];
    while (current != nullptr) {
        if (current->account_number == account_number) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int Hash_Table::remove(int account_number) {
    int index = hash_function(account_number);
    Data_Record *current = table[index];
    Data_Record *prev = nullptr;

    while (current != nullptr) {
        if (current->account_number == account_number) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            num_of_elements--;
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return 1;
}

void Hash_Table::display() const {
    bool empty_flag = true;
    for (int i = 0; i < size; i++) {
        Data_Record *current = table[i];
        if (current != nullptr) {
            empty_flag = false;
            cout << "Ячейка " << i << ":" << endl;
            while (current != nullptr) {
                cout << "  " << current->string_rep() << endl;
                current = current->next;
            }
            cout << endl;
        }
    }
    if (empty_flag) {
        cout << "Нет данных" << endl;
    }
}

