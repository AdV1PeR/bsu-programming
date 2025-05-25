#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string toHex(int num) {
    if (num == 0) return "0";
    string hex;
    while (num > 0) {
        int rem = num % 16;
        hex.push_back(rem < 10 ? '0' + rem : 'A' + rem - 10);
        num /= 16;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}

bool isPalindrome(const string& s) {
    return s == string(s.rbegin(), s.rend());
}

int main() {
    int N;
    cout << "Введите натуральное число N: ";
    cin >> N;
    cout << "Симметричные числа в шестнадцатеричной системе:\n";
    for (int i = 1; i <= N; ++i) {
        string hex = toHex(i);
        if (isPalindrome(hex)) {
            cout << "Десятичное: " << i << "; Шестнадцатеричное: " << hex << endl;
        }
    }
    return 0;
}