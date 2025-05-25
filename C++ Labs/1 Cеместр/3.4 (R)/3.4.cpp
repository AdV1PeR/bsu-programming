#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите размер матрицы n: ";
    cin >> n;

    int matrix[100][100] = { 0 };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j < n - i) {
                matrix[i][j] = i + 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }

    cout << "Сгенерированная матрица:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}