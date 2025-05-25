#include <iostream>

using namespace std;

// Четырехзначное?
bool isFourDigit(int n) {
    return n >= 1000 && n <= 9999;
}

// Цифры 9?
int countNines(int n) {
    int count = 0;
    while (n > 0) {
        if (n % 10 == 9) {
            count++;
        }
        n /= 10;
    }
    return count;
}

// С Указателем
void pointer(int n, int* count) {
    *count = countNines(n);
}

int main() {
    setlocale(LC_ALL, "RU");

    int n;

    cout << "Введите четырехзначное натуральное число: ";
    cin >> n;

    // Проверка на 4
    while (!isFourDigit(n)) {
        cout << "Ошибка: число должно быть четырехзначным. Попробуйте снова: ";
        cin >> n;
    }

    int c_nines = 0;

    // Юзаем функцию с указателем
    pointer(n, &c_nines);

    // Вывод
    if (c_nines > 2) {
        cout << "Да, число содержит более двух цифр 9." << endl;
    }
    else {
        cout << "Нет, число не содержит более двух цифр 9." << endl;
    }

    return 0;
}