#include <iostream>

using namespace std;

void generateNumbers(int N, int cNum, int lD) {

    if (cNum > 0 && cNum <= N) {
        cout << cNum << endl;
    }

    for (int i = lD - 1; i >= 0; --i) {
        generateNumbers(N, cNum * 10 + i, i);
    }
}

int main() {

    setlocale(LC_ALL, "RU");

    int N;
    cout << "Введите число N: ";
    cin >> N;

    for (int i = 1; i <= 9; ++i) {
        generateNumbers(N, i, i);
    }

    for (int i = 0; i <= 9; ++i) {
        generateNumbers(N, i, i);
    }

    return 0;
}