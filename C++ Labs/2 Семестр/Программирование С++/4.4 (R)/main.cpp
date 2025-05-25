#include "Vector.h"
#include <iostream>
#include <limits>

using std::cin, std::cout, std::endl, std::cerr;

// Функция для отображения меню
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
    cout << "11. Вычитание векторов\n";
    cout << "12. Умножение векторов\n";
    cout << "13. Деление векторов\n";
    cout << "14. Вывести вектор\n";
    cout << "15. Ввести вектор\n";
    cout << "16. Заполнить случайными числами\n";
    cout << "17. Переключить активный вектор (1/2)\n";
    cout << "18. Вычислить Z = a*X + b*Y\n";
    cout << "0. Выход\n";
    cout << "Выберите операцию: ";
}

// Функция для очистки буфера ввода
void clearInput() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функция для безопасного чтения целого числа
bool safeReadInt(int& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        clearInput();
        cout << "Ошибка: Неверный ввод! Пожалуйста, введите число.\n";
        return false;
    }
    return true;
}

// Функция для безопасного чтения числа с плавающей запятой
bool safeReadDouble(double& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        clearInput();
        cout << "Ошибка: Неверный ввод! Пожалуйста, введите число.\n";
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
        if (!safeReadInt(choice)) {
            continue;
        }

        switch (choice) {
            case 1: {
                int size;
                cout << "Введите размер: ";
                if (!safeReadInt(size)) {
                    break;
                }
                current->setSize(size);
                cout << "Размер установлен.\n";
                break;
            }
            case 2: {
                cout << "Количество элементов: " << current->getSize() << endl;
                break;
            }
            case 3: {
                int index;
                cout << "Введите индекс: ";
                if (!safeReadInt(index)) {
                    break;
                }
                cout << "Элемент: " << current->getElement(index) << endl;
                break;
            }
            case 4: {
                int index;
                double value;
                cout << "Введите индекс: ";
                if (!safeReadInt(index)) {
                    break;
                }
                cout << "Введите значение: ";
                if (!safeReadDouble(value)) {
                    break;
                }
                current->setElement(index, value);
                cout << "Значение установлено.\n";
                break;
            }
            case 5: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) {
                    break;
                }
                *current = *current + scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 6: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) {
                    break;
                }
                *current = *current - scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 7: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) {
                    break;
                }
                *current = *current * scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 8: {
                double scalar;
                cout << "Введите скаляр: ";
                if (!safeReadDouble(scalar)) {
                    break;
                }
                *current = *current / scalar;
                cout << "Результат:\n";
                current->print();
                break;
            }
            case 9: {
                cout << "Длина вектора: " << current->length() << endl;
                break;
            }
            case 10: {
                if (!vec1.checkSizeEquality(vec2)) {
                    break;
                }
                Vector res = vec1 + vec2;
                cout << "Сумма:\n";
                res.print();
                break;
            }
            case 11: {
                if (!vec1.checkSizeEquality(vec2)) {
                    break;
                }
                Vector res = vec1 - vec2;
                cout << "Разность:\n";
                res.print();
                break;
            }
            case 12: {
                if (!vec1.checkSizeEquality(vec2)) {
                    break;
                }
                Vector res = vec1 * vec2;
                cout << "Произведение:\n";
                res.print();
                break;
            }
            case 13: {
                if (!vec1.checkSizeEquality(vec2)) {
                    break;
                }
                Vector res = vec1 / vec2;
                cout << "Частное:\n";
                res.print();
                break;
            }
            case 14: {
                cout << "Вектор:\n";
                current->print();
                break;
            }
            case 15: {
                cout << "Введите элементы:\n";
                current->input();
                break;
            }
            case 16: {
                double min, max;
                cout << "Минимальное значение: ";
                if (!safeReadDouble(min)) {
                    break;
                }
                cout << "Максимальное значение: ";
                if (!safeReadDouble(max)) {
                    break;
                }
                current->fillRandom(min, max);
                cout << "Вектор заполнен.\n";
                break;
            }
            case 17: {
                // Переключение между векторами
                current = (current == &vec1) ? &vec2 : &vec1;
                cout << "Активный вектор переключен.\n";
                break;
            }
            case 18: {
                // Проверка равенства размеров векторов
                if (!vec1.checkSizeEquality(vec2)) {
                    break;
                }
                double a = vec1.max();
                double b = vec2.max();
                Vector temp1 = vec1 * a;
                Vector temp2 = vec2 * b;
                Vector Z = temp1 + temp2;
                cout << "Вектор Z (a*X + b*Y):\n";
                Z.print();
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default: {
                cout << "Ошибка: Неверный выбор операции.\n";
                break;
            }
        }
    }

    return 0;
}
