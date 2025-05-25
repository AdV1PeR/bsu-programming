#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;
const double E = 2.718281828459045;

int main() {

    setlocale(LC_ALL, "RU");

    double x;
    cout << "Введите значение 'x' (положительное число): ";
    cin >> x;

    double x_2 = pow(x, 2);
    double result = sin(log(x) + sin(PI * x_2)) * pow(x_2 + sin(x) + pow(E, cos(x)), 0.25);

    cout << "Результат y: " << result << endl;

    return 0;
}