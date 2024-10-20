//
//  hash.hpp
//  6.1
//
//  Created by Сергей Лазаренко on 30.09.2024.
//
#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Data_Record {
    int account_number;
    string full_name;
    string address;
    Data_Record *next;

    Data_Record(int account_number, const string& full_name, const string& address)
        : account_number(account_number), full_name(full_name), address(address), next(nullptr) {}

    string string_rep();
};

class Hash_Table {
private:
    Data_Record **table;
    int size;
    int num_of_elements;
    const float load_factor_threshold = 0.75;

    int hash_function(int account_number) const;
    void rehash();

public:
    Hash_Table(int table_size);
    ~Hash_Table();

    void insert(Data_Record *new_record);
    Data_Record *search(int account_number);
    int remove(int account_number);
    void display() const;
};
