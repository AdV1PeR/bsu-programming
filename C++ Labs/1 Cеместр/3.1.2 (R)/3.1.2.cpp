#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    enum Initialization{
        INPUT = 1,
        RANDOM,
        PREDEFINED
    };

    int arr[100];
    int size = 0;
    int choice;

    cout << "Введите количество элементов массива: ";
    cin >> size;

    cout << "Выберите способ заполнения массива:\n1. Ввод с клавиатуры\n2. Случайные числа\n3. Инициализация\n";
    cin >> choice;

    switch (choice) {
    case PREDEFINED: {

        // Инициализация
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }

        cout << "Массив инициализирован последовательными числами: ";
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        break;
    }
        // Р - Рандом
    case RANDOM: {
        srand(static_cast<unsigned int>(time(0)));

        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 100;
        }

        cout << "Сгенерированный массив: ";
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        break;
    }

        // Input
    case INPUT: {
        cout << "Введите элементы массива:\n";
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
        }

        cout << "Введенный массив: ";
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        break;
    }
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    // Инверсии
    int inversions = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                inversions++;
            }
        }
    }

    cout << "Количество инверсий в массиве: " << inversions << endl;

    return 0;
}