#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int arr[100];
    int size;

    cout << "Введите размер массива: ";
    cin >> size;

    int choice;
    cout << "Выберите способ заполнения массива:\n1. Инициализация (1, 2, ..., n)\n2. Случайные числа\n3. Ввод с клавиатуры\n";
    cin >> choice;

    switch (choice) {   
    case 1:
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
        break;

    case 2:
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 100;
        }
        break;

    case 3:
        cout << "Введите элементы массива:\n";
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
        }
        break;

    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    cout << "Элементы массива: ";

    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int min = 0, max = 0;
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[min]) {
            min = i;
        }
        if (arr[i] > arr[max]) {
            max = i;
        }
    }

    if (min > max) {
        swap(min, max);
    }

    int summa = 0;
    for (int i = min; i <= max; ++i) {
        summa += arr[i];
    }

    cout << "Сумма элементов между максимальным и минимальным элементами (включительно): " << summa << endl;

    return 0;
}