//
//  main.cpp
//  Praktika 5.1
//
//  Created by Сергей Лазаренко on 02.09.2024.
//

#include <iostream>
#include <bitset>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

//int main() {
//  setlocale(LC_ALL, "RUS");
//  unsigned x = 255; // 8-разрядное двоичное число 11111111
//  unsigned maska = 1; // 1=00000001 - 8-разрядная маяка
//  cout << "До преобразований: " << x << endl;
//  x = x & (~(maska << 4));
//  cout << "После преобразований: " << x << endl;
//}

//int main() {
//  setlocale(LC_ALL, "RUS");
//  unsigned x = 191; // 8-разрядное двоичное число 10111111
//  unsigned maska = 1; // 1=00000001 - 8-разрядная маяка
//  cout << "До преобразований: " << x << endl;
//  x = x | (maska << 6);
//  cout << "После преобразований: " << x << endl;
//}

//int main(){
//    
//    unsigned int x = 25;
//    const int n = sizeof(int) * 8; // = 32 - количество разрядов в числе типа int
//    unsigned maska = (1 << (n - 1)); // 1 в старшем бите 32-разрядной сетки
//    cout << "Исходная маска: " << bitset<n>(maska) << endl;
//    cout << "Результат: ";
//    for(int i = 1; i <= n; i++){
//        cout << ((x & maska) >> (n - i));
//        maska = maska >> 1; // смещение 1 в маске на разряд вправо
//    }
//    cout << endl << "Нажмите Enter для выхода...";
//    cin.get();
//    
//    return 0;
// }
// 2.a-2.б
//int main() {
//    unsigned long long mask = 0;// Битовое представление для сортировки
//    int count;// Количество чисел для ввода (до 64)
//    cout << "Введите количество чисел(1-64): ";
//    cin >> count;
//    if (count < 1 || count > 64) {
//        cout << "Неверное количество чисел" << endl;
//        return 1;
//    }
//    cout << "Введите числа(0-63): ";
//    for (int i = 0; i < count; i++) {
//        int num;
//        cin >> num;
//        if (num < 0 || num > 63) {
//            cout << "Неверное число" << endl;
//            return 1;
//        }
//        mask |= (1ULL << num);// 1ULL - unsigned long long 1
//    }
//    cout << "Битовый массив: " << bitset<64>(mask) << endl;//Установление бита в битовый массиве
//    
//    cout << "Отсортированные числа: ";
//    for (int i = 0; i < 64; i++) {
//        if (mask & (1ULL << i)) {
//            cout << i << " ";
//        }
//    }
//    cout << endl;
//    return 0;
//}
// 2.в.
//void addNum(unsigned char mask[], int num){
//    mask[num / 8] |= (1 << (num % 8));
//}
//
//bool isNum(unsigned char mask[], int num){
//    return(mask[num / 8] & (1 << (num % 8))) != 0;
//}
//
//void Print(unsigned char mask[]){
//    for(int i = 0; i < 64; i++){
//        if(isNum(mask, i)){
//            cout << i << " ";
//        }
//    }
//    cout << endl;
//}
//
//int main() {
//    unsigned char mask[8] = {0};// Каждые 8 бит - 1 байт, 64 - чисел (бит)
//    int count;// Количество чисел
//    
//    cout << "Введите количество чисел: ";
//    cin >> count; // Количество вводимых чисел
//    
//    cout << "Введите числа: ";
//    
//    for (int i = 0; i < count; i++) {
//        int num;
//        cin >> num;
//        addNum(mask, num);
//    }
//    
//    Print(mask);// Вывод массива
//    return 0;
//}
//3.a-3.б
#define MAX_BITS (1 << 27)//Определить максимальное количество бит
#define BYTE_SIZE 8 //Определить размер байта (8 бит)

int main() {
    setlocale(LC_ALL, "RUS");
    clock_t start_time = clock();

    ifstream input_file("/Users/gwynbleidd/Desktop/Praktika 5.1 2/Praktika 5.1/input123.txt");//Открытие файл ввода
    if (!input_file) {
        cerr << "Ошибка открытия файла ввода" << endl;
        return 1;
    }

    vector<unsigned char> mask((MAX_BITS + BYTE_SIZE - 1) / BYTE_SIZE, 0);//Создание массива mask
    int num;
    int count = 0;
    while (input_file >> num) {
        if (num >= 0 && num < MAX_BITS) {
            mask[num / BYTE_SIZE] |= (1 << (num % BYTE_SIZE));//Установить соответствующий бит
            count++;
        }
    }
    input_file.close();

    ofstream output_file("/Users/gwynbleidd/Desktop/Praktika 5.1 2/Praktika 5.1/output123.txt");
    if (!output_file) {
        cerr << "Ошибка открытия файла вывода" << endl;
        return 1;
    }
    for (int i = 0; i < MAX_BITS; i++) { //Перебрать массив mask
        if (mask[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) { //Проверить, установлен ли бит
            output_file << i << " "; //Вывести индекс установленного бита
        }
    }
    output_file.close();

    clock_t end_time = clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Время работы: %.2f секунд\n", elapsed_time);
    
    size_t memory_usage = mask.size() * sizeof(mask[0]);//Путем умножения кол-во элементов на размер каждого
    cout << "Объем памяти: " << memory_usage << " бит" << endl;
    return 0;
}
