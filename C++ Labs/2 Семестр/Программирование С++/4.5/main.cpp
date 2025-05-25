#include "Vector.h"
#include <iostream>
#include <limits>

using std::cin, std::cout, std::endl, std::cerr;

void displayMenu() {
    cout << "\n=== ВЕКТОРНЫЕ ОПЕРАЦИИ ===\n";
    cout << "1. Задать размерность вектора\n";
    cout << "2. Получить количество элементов\n";
    cout << "3. Получить элемент по индексу\n";
    cout << "4. Установить элемент по индексу\n";
    cout << "5. Сложение с скаляром\n";
    cout << "6. Вычитание скаляра\n";
    cout << "7. Умножение на скаляр\n";
    cout << "8. Деление на скаляр\n";
    cout << "9. Вычислить длину вектора\n";
    cout << "10. Сложение векторов\n";
    cout << "11. Вычитание векторов (метод класса)\n";
    cout << "12. Вычитание векторов (внешняя функция)\n";
    cout << "13. Умножение векторов\n";
    cout << "14. Деление векторов\n";
    cout << "15. Вывести вектор\n";
    cout << "16. Ввести вектор\n";
    cout << "17. Заполнить случайными числами\n";
    cout << "18. Переключить активный вектор (1/2)\n";
    cout << "0. Выход\n";
    cout << "Выберите операцию: ";
}

void clearInput() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool safeReadInt(int& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        clearInput();
        cout << "Ошибка: Неверный ввод!\n";
        return false;
    }
    return true;
}

bool safeReadDouble(double& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        clearInput();
        cout << "Ошибка: Неверный ввод!\n";
        return false;
    }
    return true;
}

int main() {
    Vector vec1, vec2;
    Vector* current = &vec1;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        if (!safeReadInt(choice)) continue;

        switch (choice) {
            case 1: {
                int size;
                cout << "Введите размер: ";
                if (!safeReadInt(size)) break;
                current->setSize(size);
                cout << "Размер установлен.\n";
                break;
            }
            case 2:
                cout << "Количество элементов: " << current->getSize() << endl;
                break;
            case 3: {
                int index;
                cout << "Введите индекс: ";
                if (!safeReadInt(index)) break;
                cout << "Элемент: " << current->getElement(index) << endl;
                break;
            }
            case 4: {
                int index;
                double value;
                cout << "Введите индекс: ";
                if (!safeReadInt(index)) break;
                cout << "Введите значение: ";
                if (!safeReadDouble(value)) break;
                current->setElement(index, value);
                cout << "Значение установлено.\n";
                break;
            }
            case 5: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) break;
                *current = *current + scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 6: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) break;
                *current = *current - scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 7: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) break;
                *current = *current * scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 8: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) break;
                *current = *current / scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 9:
                cout << "Длина вектора: " << current->length() << endl;
                break;
            case 10: {
                if (!vec1.checkSizeEquality(vec2)) break;
                Vector res = vec1 + vec2;
                cout << "Сумма:\n";
                res.print();
                break;
            }
            case 11: {
                if (!vec1.checkSizeEquality(vec2)) break;
                Vector res = vec1 - vec2; // метод класса
                cout << "Разность (метод класса):\n";
                res.print();
                break;
            }
            case 12: {
                if (!vec1.checkSizeEquality(vec2)) break;
                Vector res = vec1 - vec2; // вызов метода класса
                cout << "Разность (внешняя функция):\n";
                res.print();
                break;
            }
            case 13: {
                if (!vec1.checkSizeEquality(vec2)) break;
                Vector res = vec1 * vec2;
                cout << "Произведение:\n";
                res.print();
                break;
            }
            case 14: {
                if (!vec1.checkSizeEquality(vec2)) break;
                Vector res = vec1 / vec2;
                cout << "Частное:\n";
                res.print();
                break;
            }
            case 15:
                cout << "Вектор:\n";
                current->print();
                break;
            case 16:
                cout << "Введите элементы:\n";
                current->input();
                break;
            case 17: {
                double min, max;
                cout << "Минимальное значение: ";
                if (!safeReadDouble(min)) break;
                cout << "Максимальное значение: ";
                if (!safeReadDouble(max)) break;
                current->fillRandom(min, max);
                cout << "Вектор заполнен.\n";
                break;
            }
            case 18:
                current = (current == &vec1) ? &vec2 : &vec1;
                cout << "Активный вектор: " << (current == &vec1 ? "1" : "2") << endl;
                break;
            case 0:
                running = false;
                cout << "Выход...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    }

    return 0;
}
