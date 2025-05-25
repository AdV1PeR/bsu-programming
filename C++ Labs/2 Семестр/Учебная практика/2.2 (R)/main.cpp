#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void printChetnyiColumns(int* arr, int rows, int cols) {
    cout << "Номера столбцов с четными элементами (одномерный массив): ";
    for (int j = 0; j < cols; j++) {
        bool allChetnyi = true;
        for (int i = 0; i < rows; i++) {
            if (arr[i * cols + j] % 2 != 0) {
                allChetnyi = false;
                break;
            }
        }
        if (allEven) {
            cout << j << " ";
        }
    }
    cout << endl;
}

void printChetnyiColumns(int** arr, int rows, int cols) {
    cout << "Номера столбцов с четными элементами (двумерный массив): ";
    for (int j = 0; j < cols; j++) {
        bool allChetnyi = true;
        for (int i = 0; i < rows; i++) {
            if (arr[i][j] % 2 != 0) {
                allChetnyi = false;
                break;
            }
        }
        if (allEven) {
            cout << j << " ";
        }
    }
    cout << endl;
}

void create_two_to_one(int rows, int cols) {
    int* arr = new int[rows * cols];
    cout << "Двумерный массив (одномерный):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i * cols + j] = rand() % 10;
            cout << arr[i * cols + j] << " ";
        }
        cout << endl;
    }

    printChetnyiColumns(arr, rows, cols);
    delete[] arr;
}

void createPointers(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    cout << "Двумерный массив (указатель на массив указателей):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    printChetnyiColumns(arr, rows, cols);

    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() {
    int rows, cols;
    srand(static_cast<unsigned int>(time(0)));

    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;

    create_two_to_one(rows, cols);
    createPointers(rows, cols);

    return 0;
}
