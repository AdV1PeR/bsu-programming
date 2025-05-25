#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int minColumnSum(const vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;

    int min_sum = 0;
    for (const auto& row : matrix) {
        min_sum += abs(row.at(0));
    }

    for (size_t j = 1; j < matrix[0].size(); ++j) {
        int current_sum = 0;
        for (const auto& row : matrix) {
            current_sum += abs(row.at(j));
        }
        if (current_sum < min_sum) {
            min_sum = current_sum;
        }
    }
    return min_sum;
}

vector<vector<int>> inputMatrix() {
    int rows, cols;
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;

    vector<vector<int>> matrix;
    matrix.resize(rows);
    for (auto& row : matrix) {
        row.resize(cols);
        cout << "Введите " << cols << " элементов строки: ";
        for (auto& el : row) {
            cin >> el;
        }
    }
    return matrix;
}

vector<vector<int>> generateRandomMatrix(int rows, int cols) {
    vector<vector<int>> matrix;
    matrix.resize(rows);
    for (auto& row : matrix) {
        row.resize(cols);
        for (auto& el : row) {
            el = rand() % 19 - 9;
        }
    }
    return matrix;
}

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "\nМатрица:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> handleUserChoice(int choice) {
    vector<vector<int>> matrix;
    if (choice == 1) {
        matrix = inputMatrix();
    } else if (choice == 2) {
        int rows, cols;
        cout << "Введите количество строк: ";
        cin >> rows;
        cout << "Введите количество столбцов: ";
        cin >> cols;
        matrix = generateRandomMatrix(rows, cols);
        printMatrix(matrix);
    } else {
        cout << "Неверный выбор!\n";
        exit(1);
    }
    return matrix;
}

void printResult(int result) {
    cout << "\nМинимальная сумма модулей элементов столбца: " << result << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int choice;
    cout << "Выберите способ задания матрицы:\n";
    cout << "1. Ввести матрицу вручную\n";
    cout << "2. Сгенерировать случайную матрицу\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    vector<vector<int>> matrix = handleUserChoice(choice);
    int result = minColumnSum(matrix);
    printResult(result);

    return 0;
}
