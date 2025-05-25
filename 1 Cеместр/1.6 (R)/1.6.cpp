#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int x, y;

    cout << "Введите значение x: ";
    cin >> x;

    cout << "Введите значение y: ";
    cin >> y;

    if (x > 0 && y > 0) {
        x = -x;
        y = -y;
    }
    else if (x > 0 || y > 0) {
        x -= 2.5;
        y -= 2.5;
    }
    else if (x < 0 && y < 0 && ((x >= -5 && x <= -2) || (y >= -5 && y <= -2))) {
        x *= 10;
        y *= 10;
    }

    cout << "Результат: x = " << x << ", y = " << y << endl;

    return 0;
}   