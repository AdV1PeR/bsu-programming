#include <iostream>
#include <cmath>

using namespace std;

double calculateResult(double x, double PI, double E) {
    double x_2 = pow(x, 2);
    double result = sin(log(x) + sin(PI * x_2)) * pow(x_2 + sin(x) + pow(E, cos(x)), 0.25);
    return result;
}

int main() {

    setlocale(LC_ALL, "RU");

    double x;
    const double PI = 3.141592653589793;
    const double E = 2.718281828459045;

    cout << "Введите значение 'x' (положительное число): ";
    cin >> x;

    if (x <= 0) {
        cout << "Ошибка: 'x' должно быть положительным числом." << endl;
        return 1;
    }

    double result = calculateResult(x, PI, E);

    cout << "Результат y: " << result << endl;

    return 0;
}