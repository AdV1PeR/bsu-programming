#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string toHex(int num) { // 16
    string hex;
    while (num > 0) {
        int rem = num % 16;
        if (rem < 10) {
            hex += (rem + '0');
        }
        else {
            hex += (rem - 10 + 'A');
        }
        num /= 16;
    }
    reverse(hex.begin(), hex.end()); // Порядок
    return hex;
}

bool isPalindrome(const string& str) { // Полиндром?
    return str == string(str.rbegin(), str.rend());
}

void findSymmetricNumbers(int N) { // Поиск
    cout << "Симметричные числа в шестнадцатеричной системе счисления:\n";
    for (int i = 1; i <= N; ++i) {
        string hex = toHex(i);
        if (isPalindrome(hex)) {
            cout << "Десятичное: " << i << "; Шестнадцатеричное: " << hex << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int N;
    cout << "Введите натуральное число N: ";
    cin >> N;

    findSymmetricNumbers(N);

    return 0;
}