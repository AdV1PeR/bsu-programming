#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функция для заполнения массива по возрастанию
void fillAscending(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = i + 1; // Заполняем числами от 1 до n
    }
}

// Функция для заполнения массива по убыванию
void fillDescending(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = arr.size() - i; // Заполняем числами от n до 1
    }
}

// Функция для заполнения массива случайными числами
void fillRandom(vector<int>& arr) {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = rand() % 100; // Заполняем случайными числами от 0 до 99
    }
}

// Функция для выбора способа заполнения массива
void chooseFillingMethod(vector<int>& arr) {
    int choice;
    cout << "Выберите способ заполнения массива:\n";
    cout << "1. По возрастанию\n";
    cout << "2. По убыванию\n";
    cout << "3. Случайно\n";
    cin >> choice;

    switch (choice) {
        case 1:
            fillAscending(arr);
            break;
        case 2:
            fillDescending(arr);
            break;
        case 3:
            fillRandom(arr);
            break;
        default:
            cout << "Неверный выбор! Заполнение по умолчанию (случайно).\n";
            fillRandom(arr);
            break;
    }
}

// Функция для вывода массива
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Функция пузырьковой сортировки
void bubbleSort(vector<int>& arr, int& comparisons, int& movements) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                movements++;
            }
        }
    }
}

// Функция сортировки вставками
void insertionSort(vector<int>& arr, int& comparisons, int& movements) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        comparisons++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            movements++;
            comparisons++;
        }
        arr[j + 1] = key;
        movements++;
    }
}

// Функция для выбора метода сортировки
void chooseSortingMethod(vector<int>& arr) {
    int choice;
    cout << "Выберите метод сортировки:\n";
    cout << "1. Пузырьковая сортировка\n";
    cout << "2. Сортировка вставками\n";
    cin >> choice;

    int comparisons = 0;
    int movements = 0;

    switch (choice) {
        case 1:
            bubbleSort(arr, comparisons, movements);
            cout << "Массив после пузырьковой сортировки: ";
            break;
        case 2:
            insertionSort(arr, comparisons, movements);
            cout << "Массив после сортировки вставками: ";
            break;
        default:
            cout << "Неверный выбор! Сортировка не выполнена.\n";
            return;
    }

    printArray(arr);
    cout << "Сравнения: " << comparisons << ", Перемещения: " << movements << endl;
}

// Основная функция
int main() {
    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    vector<int> arr(size);

    // Вызов функции для выбора способа заполнения массива
    chooseFillingMethod(arr);

    // Вывод заполненного массива
    cout << "Заполненный массив: ";
    printArray(arr);

    // Вызов функции для выбора метода сортировки
    chooseSortingMethod(arr);

    return 0;
}
