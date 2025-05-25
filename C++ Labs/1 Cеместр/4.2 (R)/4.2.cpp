#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int N;
    cout << "Введите натуральное число N: ";
    cin >> N;

    cout << "Симметричные числа в шестнадцатеричной системе счисления:\n";

    for (int i = 1; i <= N; ++i) {
        string hex;
        int num = i;

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

        reverse(hex.begin(), hex.end());

        if (hex == string(hex.rbegin(), hex.rend())) {
            cout << "Десятичное: " << i << "; Шестнадцатеричное: " << hex << endl;
        }
    }

    return 0;
}