#include <iostream>

using namespace std;

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

int summa(const int arr[], int size) {
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

    int sum = 0;
    for (int i = min; i <= max; ++i) {
        sum += arr[i];
    }

    return sum;
}

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
        init(arr, size);
        break;

    case 2:
        random(arr, size);
        break;

    case 3:
        input(arr, size);
        break;

    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    print(arr, size);

    int sum = summa(arr, size);
    cout << "Сумма элементов между максимальным и минимальным элементами (включительно): " << sum << endl;

    return 0;
}