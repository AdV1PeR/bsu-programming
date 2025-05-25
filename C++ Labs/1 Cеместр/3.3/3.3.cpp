#include <iostream>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите размер матрицы (кратный 6): ";
    cin >> n;

    // Кратен 6?
    if (n % 6 != 0) {
        cout << "Ошибка: размер матрицы должен быть кратен 6." << endl;
        return 1;
    }

    vector<vector<double>> matrix(n, vector<double>(n));
    srand(static_cast<unsigned int>(time(0)));

    cout << "Сгенерированная матрица:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = static_cast<double>(rand() % 2);
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i == 0 && (j == 0 || j == n - 1)) ||   // 1
                (i == 1 && (j < 2 || j >= n - 2)) ||    // 2
                (i == 2) ||                             // 3
                (i == 3) ||                             // 4
                (i == 4 && (j < 2 || j >= n - 2)) ||    // 5
                (i == 5 && (j == 0 || j == n - 1))) {   // 6
                sum += matrix[i][j];
            }
        }
    }

    cout << "Сумма элементов закрашенной части матрицы: " << sum << endl;

    return 0;
}