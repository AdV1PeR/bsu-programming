#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cin; using std::endl;
using std::cout; using std::swap;

template <typename T>
void fillUp(T* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<T>(i + 1);
    }
}

template <typename T>
void fillDown(T* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<T>(size - i);
    }
}

template <typename T>
void fillRandom(T* arr, int size) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<T>(rand() % 100);
    }
}

template <typename T>
void chooseFillingMethod(T* arr, int size) {
    int choice;
    cout << "Выберите способ заполнения массива:\n1. По возрастанию\n2. По убыванию\n3. Случайно\n";
    cin >> choice;

    switch (choice) {
        case 1:
            fillUp(arr, size);
            break;
        case 2:
            fillDown(arr, size);
            break;
        case 3:
            fillRandom(arr, size);
            break;
        default:
            cout << "Cовсем что-ли..?! Написано же, 1 2 3";
            break;
    }
}

template <typename T>
void printArray(const T* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
void bubbleSort(T* arr, int size, int& comparisons, int& movements) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                movements++;
            }
        }
    }
}

template <typename T>
void insertionSort(T* arr, int size, int& comparisons, int& movements) {
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
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

template <typename T>
void chooseSortingMethod(T* arr, int size) {
    int choice;
    cout << "Выберите метод сортировки:\n1. Пузырьковая сортировка\n2. Сортировка вставками\n";
    cin >> choice;

    int comparisons = 0;
    int movements = 0;

    switch (choice) {
        case 1:
            bubbleSort(arr, size, comparisons, movements);
            cout << "Массив после пузырьковой сортировки: ";
            break;
        case 2:
            insertionSort(arr, size, comparisons, movements);
            cout << "Массив после сортировки вставками: ";
            break;
        default:
            cout << "Неверный выбор! Сортировка не выполнена.\n";
            return;
    }

    printArray(arr, size);
    cout << "Сравнения: " << comparisons << ", Перемещения: " << movements << endl;
}

int chooseDataType() {
    int typeChoice;
    cout << "Выберите тип данных:\n1. int\n2. float\n3. double\n4. char\n";
    cin >> typeChoice;
    return typeChoice;
}

void processArrayByType(int typeChoice, int size) {
    switch (typeChoice) {
        case 1: {
            int* arr = new int[size];
            chooseFillingMethod(arr, size);
            cout << "Заполненный массив: ";
            printArray(arr, size);
            chooseSortingMethod(arr, size);
            delete[] arr;
            break;
        }
        case 2: {
            float* arr = new float[size];
            chooseFillingMethod(arr, size);
            cout << "Заполненный массив: ";
            printArray(arr, size);
            chooseSortingMethod(arr, size);
            delete[] arr;
            break;
        }
        case 3: {
            double* arr = new double[size];
            chooseFillingMethod(arr, size);
            cout << "Заполненный массив: ";
            printArray(arr, size);
            chooseSortingMethod(arr, size);
            delete[] arr;
            break;
        }
        case 4: {
            char* arr = new char[size];
            chooseFillingMethod(arr, size);
            cout << "Заполненный массив: ";
            printArray(arr, size);
            chooseSortingMethod(arr, size);
            delete[] arr;
            break;
        }
        default:
            cout << "Неверный выбор типа даУнных!" << endl;
            break;
    }
}

int main() {
    int size;
    cout << "Введите размер массива: ";
    cin >> size;

    int typeChoice = chooseDataType();
    processArrayByType(typeChoice, size);

    return 0;
}
