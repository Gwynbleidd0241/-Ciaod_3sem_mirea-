//
//  main.cpp
//  6.1
//
//  Created by Сергей Лазаренко on 30.09.2024.
//
#include "hash.hpp"
#include <limits>

Hash_Table bankAccounts(5);

void add_initial_records() {
    bankAccounts.insert(new Data_Record(1234567, "Лазаренко Сергей Александрович", "ул. Нарвская, д.12"));
    bankAccounts.insert(new Data_Record(2345678, "Петров Сергей Петрович", "ул. Гагарина, д.5"));
    bankAccounts.insert(new Data_Record(3456789, "Сидоров Сидор Сидорович", "ул. Мира, д.10"));
    bankAccounts.insert(new Data_Record(4567890, "Николаев Николай Николаевич", "ул. Победы, д.2"));
    bankAccounts.insert(new Data_Record(5678901, "Федоров Федор Федорович", "ул. Парковая, д.3"));
}

void clear_cin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int get_account_number_from_user() {
    int account_number;
    while (true) {
        cout << "Введите номер счета (7-значное число): ";
        if (cin >> account_number && account_number >= 1000000 && account_number <= 9999999) {
            clear_cin();
            return account_number;
        }
        clear_cin();
        cout << "Неверный номер счета. Пожалуйста, введите 7-значное число.\n";
    }
}

string get_string_from_user(string prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

void insert() {
    int account_number = get_account_number_from_user();
    string name = get_string_from_user("Введите ФИО: ");
    string address = get_string_from_user("Введите адрес: ");
    Data_Record* new_record = new Data_Record(account_number, name, address);
    bankAccounts.insert(new_record);
    cout << "Успешно добавлен новый счет: " << new_record->string_rep() << endl;
}

void del() {
    int account_number = get_account_number_from_user();
    int return_code = bankAccounts.remove(account_number);
    if (return_code == 0) {
        cout << "Счет с номером " << account_number << " успешно удален." << endl;
    } else {
        cout << "Счет с номером " << account_number << " не найден." << endl;
    }
}

void search() {
    int account_number = get_account_number_from_user();
    Data_Record* record = bankAccounts.search(account_number);
    if (record == nullptr) {
        cout << "Счет с номером " << account_number << " не найден." << endl;
    } else {
        cout << "Найден счет: " << record->string_rep() << endl;
    }
}

void display() {
    cout << "Отображение всех счетов: " << endl;
    bankAccounts.display();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    add_initial_records();

    int cmd;
    while (true) {
        while (true) {
            cout << "1: Добавить новый счет" << endl;
            cout << "2: Удалить счет" << endl;
            cout << "3: Поиск счета" << endl;
            cout << "4: Отобразить все счета" << endl;
            cout << "0: Выйти" << endl;
            cout << "\tВаш выбор: ";
            if (cin >> cmd && cmd >= 0 && cmd <= 4) break;
            clear_cin();
            cout << "Неверный код команды.\n";
        }

        switch (cmd) {
            case 0:
                return 0;
            case 1:
                insert();
                break;
            case 2:
                del();
                break;
            case 3:
                search();
                break;
            case 4:
                display();
                break;
        }
    }
}
