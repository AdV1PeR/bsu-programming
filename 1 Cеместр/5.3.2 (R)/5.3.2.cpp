#include <iostream>

using namespace std;

enum Initialization {
    INPUT = 1,
    RANDOM,
    PREDEFINED
};

void init(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
}

void random(int arr[], int size) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;
    }
}

void input(int arr[], int size) {
    cout << "Введите элементы массива:\n";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
}


void print(const int arr[], int size) {
    cout << "Элементы массива: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int countInversions(const int arr[], int size) {
    int inversions = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

int main() {
    setlocale(LC_ALL, "RU");

    int arr[100];
    int size = 0;
    int choice;

    cout << "Введите количество элементов массива: ";
    cin >> size;

    cout << "Выберите способ заполнения массива:\n1. Ввод с клавиатуры\n2. Случайные числа\n3. Инициализация\n";
    cin >> choice;

    switch (choice) {
    case PREDEFINED:
        init(arr, size);
        print(arr, size);
        break;

    case RANDOM:
        random(arr, size);
        print(arr, size);
        break;

    case INPUT:
        input(arr, size);
        print(arr, size);
        break;

    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    int inversions = countInversions(arr, size);
    cout << "Количество инверсий в массиве: " << inversions << endl;

    return 0;
}