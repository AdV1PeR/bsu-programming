#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

enum Initialization {
    INPUT = 1,
    RANDOM,
    PREDEFINED
};

void input(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];    
        }
    }
}

void random(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void init(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    int value = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = value++;
        }
    }
}

void print(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для нахождения наибольшего элемента на главной и побочной диагоналях
    pair<int, int> findMDE(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    int maxE = numeric_limits<int>::min();
    int row = -1;

    for (int i = 0; i < n; ++i) {

        if (matrix[i][i] > maxE) {    // Главная диагональ
            maxE = matrix[i][i];
            row = i;
        }

        if (matrix[i][n - 1 - i] > maxE) {    // Побочная диагональ
            maxE = matrix[i][n - 1 - i];
            row = i;
        }
    }
    return { maxE, row };
}

// Ортофосфор?
bool isOnal(int matrix[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; ++i) {
        int lol = 0;
        for (int j = 0; j < n; ++j) {
            lol += matrix[i][j] * matrix[i][j];
        }
        if (lol != 1) {
            return false; // Скалярное произведение строки на себя не равно 1
        }
        for (int j = i + 1; j < n; ++j) {
            int kek = 0;
            for (int k = 0; k < n; ++k) {
                kek += matrix[i][k] * matrix[j][k];
            }
            if (kek != 0) {
                return false; // Скалярное произведение различных строк не равно 0
            }
        }
    }
    return true;
}
int main() {

    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите размер матрицы n: ";
    cin >> n;

    if (n > MAX_SIZE) {
        cout << "Размер матрицы не должен превышать " << MAX_SIZE << endl;
        return 1;
    }

    int matrix[MAX_SIZE][MAX_SIZE];

    cout << "Выберите способ инициализации матрицы:\n1 - Ввод с клавиатуры\n2 - Случайные числа\n3 - Предопределенные значения\n";
    int choice;
    cin >> choice;

    switch (choice) {
    case INPUT:
        input(matrix, n);
        break;

    case RANDOM:
        random(matrix, n);
        cout << "Сгенерированная матрица:" << endl;
        print(matrix, n);
        break;

    case PREDEFINED:
        init(matrix, n);
        cout << "Предопределенная матрица:" << endl;
        print(matrix, n);
        break;

    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    pair<int, int> maxDiagonalElement = findMDE(matrix, n);
    int maxElement = maxDiagonalElement.first;
    int row = maxDiagonalElement.second;

    cout << "Наибольший элемент на главной и побочной диагоналях: " << maxElement
        << " (строка " << row << ")" << endl;

    if (isOnal(matrix, n)) {
        cout << "Матрица является ортогональной." << endl;
    }
    else {
        cout << "Матрица не является ортогональной." << endl;
    }

    return 0;
}