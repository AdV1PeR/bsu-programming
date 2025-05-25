#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

int main() {
    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите n (порядок матрицы 2n): ";
    cin >> n;

    if (n > MAX_SIZE / 2) {
        cout << "Размер матрицы слишком большой!" << endl;
        return 1;
    }

    int original[2 * MAX_SIZE][2 * MAX_SIZE];
    int newMatrix[2 * MAX_SIZE][2 * MAX_SIZE];

    cout << "Выберите способ заполнения матрицы:\n1. Случайные значения\n2. Ввод значений\n3. Инициализация значениями\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < 2 * n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                original[i][j] = rand() % 10;
            }
        }
    }
    else if (choice == 2) {
        cout << "Введите элементы матрицы (" << 2 * n << "x" << 2 * n << "):\n";
        for (int i = 0; i < 2 * n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                cin >> original[i][j];
            }
        }
    }
    else if (choice == 3) {
        int value = 1;
        for (int i = 0; i < 2 * n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                original[i][j] = value++;
            }
        }
    }
    else {
        cout << "Неверный выбор.\n";
        return 1;
    }

    cout << "Оригинальная матрица:\n";
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            cout << original[i][j] << ' ';
        }
        cout << endl;
    }

    // Перестановка
    for (int i = 0; i < n; ++i) {   
        for (int j = 0; j < n; ++j) {
            // Сохраняем
            int temp1 = original[i][j];               // Блок 1
            int temp2 = original[i][j + n];           // Блок 2
            int temp3 = original[i + n][j + n];       // Блок 3
            int temp4 = original[i + n][j];           // Блок 4

            // Перемещаем
            newMatrix[i][j + n] = temp1;              // Блок 1 в Блок 2
            newMatrix[i + n][j + n] = temp2;          // Блок 2 в Блок 3
            newMatrix[i + n][j] = temp3;               // Блок 3 в Блок 4
            newMatrix[i][j] = temp4;                   // Блок 4 в Блок 1
        }
    }

    cout << "Новая матрица после перестановки блоков:\n";
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            cout << newMatrix[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}