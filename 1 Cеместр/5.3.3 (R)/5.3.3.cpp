#include <iostream>
#include <vector>

using namespace std;

enum Initialization {
    INPUT = 1,
    RANDOM,
    PREDEFINED
};

void input(vector<int>& arr) {
    cout << "Введите элементы массива:\n";
    for (int& num : arr) {
        cin >> num;
    }
}

void random(vector<int>& arr) {
    srand(static_cast<unsigned int>(time(0)));
    for (int& num : arr) {
        num = rand() % 201 - 100;
    }
}

void print(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Сортировка
vector<int> sortBySign(const vector<int>& arr) {
    vector<int> result;

    // +
    for (int num : arr) {
        if (num > 0) {
            result.push_back(num);
        }
    }

    // -
    for (int num : arr) {
        if (num < 0) {
            result.push_back(num);
        }
    }

    // 0
    for (int num : arr) {
        if (num == 0) {
            result.push_back(num);
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "RU");

    int size = 0;
    int choice;

    cout << "Введите количество элементов массива: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Выберите способ заполнения массива:\n1. Ввод с клавиатуры\n2. Случайные числа\n3. Ввод предопределенного массива\n";
    cin >> choice;

    switch (choice) {
    case INPUT:
        input(arr);
        break;

    case RANDOM:
        random(arr);
        cout << "Сгенерированный массив: ";
        print(arr);
        break;

    case PREDEFINED:
        input(arr);
        break;

    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    vector<int> sortedArray = sortBySign(arr);

    cout << "Новый массив: ";
    print(sortedArray);

    return 0;
}