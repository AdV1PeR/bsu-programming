#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    double x, y;

    cout << "Введите значение x: ";
    cin >> x;

    cout << "Введите значение y: ";
    cin >> y;

    x = (x > 0 && y > 0) ? -x :
        (x > 0 || y > 0) ? (x - 2.5) :
        (x < 0 && y < 0 && ((x >= -5 && x <= -2) || (y >= -5 && y <= -2))) ? (x * 10) : x;

    y = (x > 0 && y > 0) ? -y :
        (x > 0 || y > 0) ? (y - 2.5) :
        (x < 0 && y < 0 && ((x >= -5 && x <= -2) || (y >= -5 && y <= -2))) ? (y * 10) : y;

    cout << "Результат: x = " << x << ", y = " << y << endl;

    return 0;
}