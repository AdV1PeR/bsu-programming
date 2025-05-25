#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    double x, y;
    cout << "Введите значение X: ";
    cin >> x;

    if (x >= -6 && x <= -2) { // 1 Прямая
        y = (1.0 / 4) * x + (3.0 / 2);
        cout << "Функция Y равна: " << y << endl;
    }
    if (x >= -2 && x <= 0) { // 1 Радиус
        y = sqrt(1.5 - pow(x + 2, 2));
        cout << "Функция Y равна: " << y << endl;
    }
    else if (x >= 0 && x <= 2) { // 2 Радиус
        y = sqrt(4 - pow(x, 2));
        cout << "Функция Y равна: " << y << endl;
    }
    else if (x > 2 && x <= 3) { // 2 Прямая
        y = x - 1;
        cout << "Функция Y равна: " << y << endl;
    }
    else {
        cout << "Значение X вне диапазона!" << endl;
    }
    return 0;
}