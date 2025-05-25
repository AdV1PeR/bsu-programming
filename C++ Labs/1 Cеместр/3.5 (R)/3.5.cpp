#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    srand(static_cast<unsigned int>(time(0)));

    int n;
    cout << "Введите порядок матрицы n: ";
    cin >> n;

    vector<vector<char>> matrix(n, vector<char>(n));

    for (int i = 0; i < n; ++i) {    // Рандинт
        for (int j = 0; j < n; ++j) {
            int r = rand() % 52; // 26 заглавных + 26 строчных
            if (r < 26) {
                matrix[i][j] = 'A' + r;
            }
            else {
                matrix[i][j] = 'a' + (r - 26);
            }
        }
    }

    cout << "Сгенерированная матрица:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    int minC = n + 1; // Максимально количество различных символов
    int minR = -1;

    // Чекаем строки матрицы
    for (int i = 0; i < n; ++i) {
        set<char> dChars; // Множество

        for (int j = 0; j < n; ++j) {
            dChars.insert(matrix[i][j]);
        }

        int Count = dChars.size(); // Количество различных символов

        // Минимальная строка?
        if (Count < minC) {
            minC = Count;
            minR = i;
        }
    }

    if (minR != -1) {
        cout << "Номер первой строки с наименьшим количеством различных символов: " << minR + 1 << endl;
    }
    else {
        cout << "Матрица пуста." << endl;
    }

    return 0;
}