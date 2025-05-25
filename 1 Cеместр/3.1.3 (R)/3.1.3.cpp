#include <iostream>
#include <vector>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    enum Initialization{
        INPUT = 1,
        RANDOM,
        PREDEFINED
    };

    int size = 0;
    int choice;

    cout << "Введите количество элементов массива: ";
    cin >> size;

    vector<int> arr(size); // Динамического размерa
    cout << "Выберите способ заполнения массива:\n1. Инициализация (ввод с клавиатуры)\n2. Случайные числа\n3. Ввод предопределенного массива\n";
    cin >> choice;

    switch (choice) {
    case INPUT: {         // Инициализация

        cout << "Введите элементы массива:\n";
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
        }
        break;
    }

    case RANDOM: {         // Рандом
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 201 - 100;
        }

        cout << "Сгенерированный массив: ";
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        break;
    }
                            
    case PREDEFINED: {      // Ввод
        cout << "Введите элементы массива:\n";
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
        }
        break;
    }
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }


    vector<int> r;     // +, -, 0

    for (int num : arr) {   // +
        if (num > 0) {
            r.push_back(num);
        }
    }

    for (int num : arr) {   // -
        if (num < 0) {
            r.push_back(num);
        }
    }


    for (int num : arr) {   // 0
        if (num == 0) {
            r.push_back(num);
        }
    }

    // Резулт
    cout << "Новый массив: ";
    for (int num : r) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}