#include <iostream>
#include <vector>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    enum Initialization {
        INPUT = 1,
        RANDOM,
        PREDEFINED
    };

    int n;
    cout << "Введите размер матрицы n: ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    cout << "Выберите способ инициализации матрицы:\n1 - Ввод с клавиатуры\n2 - Случайные числа\n3 - Предопределенные значения\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case INPUT:
        cout << "Введите элементы матрицы:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> matrix[i][j];
            }
        }
        break;

    case RANDOM:
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = rand() % 10; 
            }
        }

        cout << "Сгенерированная матрица:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        break;


    case PREDEFINED:
        int value = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = value++;
            }
        }
        cout << "Предопределенная матрица:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        break;
    }

    int row;
    int maxE = numeric_limits<int>::min();
    row = -1;

    for (int i = 0; i < n; ++i) {
        // Главная диагональ
        if (matrix[i][i] > maxE) {
            maxE = matrix[i][i];
            row = i;
        }
        // Побочная диагональ
        if (matrix[i][n - 1 - i] > maxE) {
            maxE = matrix[i][n - 1 - i];
            row = i;
        }
    }
    cout << "Наибольший элемент на главной и побочной диагоналях: " << maxE
        << " (строка " << row << ")" << endl;

    // Ортогональность?
    bool isOnal = true;
    for (int i = 0; i < n; ++i) {
        int lol = 0;
        for (int j = 0; j < n; ++j) {
            lol += matrix[i][j] * matrix[i][j];
        }
        if (lol != 1) {
            isOnal = false; // Скалярное произведение строки на себя не равно 1
            break;
        }
        for (int j = i + 1; j < n; ++j) {
            int kek = 0;
            for (int k = 0; k < n; ++k) {
                kek += matrix[i][k] * matrix[j][k];
            }
            if (kek != 0) {
                isOnal = false; // Скалярное произведение различных строк не равно 0
                break;
            }
        }
    }

    if (isOnal) {
        cout << "Матрица является ортогональной." << endl;
    }
    else {
        cout << "Матрица не является ортогональной." << endl;
    }

    return 0;
}