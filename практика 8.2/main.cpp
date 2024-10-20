#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для нахождения минимального количества монет для суммы S
int minCoins(vector<int>& coins, int S) {
    int count = 0;
    sort(coins.rbegin(), coins.rend());

    for (int coin : coins) {
        if (S == 0) break; 
        int numCoins = S / coin;
        count += numCoins;
        S -= numCoins * coin;
    }

    if (S != 0) {
        cout << "Невозможно набрать сумму этими монетами." << endl;
        return -1;
    }

    return count;
}

int main() {
    int n, S;
    cout << "Введите количество номиналов монет: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Введите номиналы монет: ";
    for (int i = 0; i < n; ++i) {
        cin >> coins[i];
    }

    cout << "Введите сумму, которую нужно набрать: ";
    cin >> S;

    int result = minCoins(coins, S);
    if (result != -1) {
        cout << "Минимальное количество монет: " << result << endl;
    }

    return 0;
}
