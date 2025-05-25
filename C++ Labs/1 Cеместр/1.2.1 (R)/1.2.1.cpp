#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int n;

    cout << "Введите четырехзначное натуральное число: ";
    cin >> n;

    while (n < 1000 || n > 9999) {
        cout << "Ошибка: число должно быть четырехзначным. Попробуйте снова: ";
        cin >> n;
    }

    int c_nines = 0;
    int a = n;

    while (a > 0) {
        int b = a % 10;
        if (b == 9) {
            c_nines++;
        }
        a /= 10;
    }   

    if (c_nines > 2) {
        cout << "Да, число содержит более двух цифр 9." << endl;
    }
    else {
        cout << "Нет, число не содержит более двух цифр 9." << endl;
    }

    return 0;
}