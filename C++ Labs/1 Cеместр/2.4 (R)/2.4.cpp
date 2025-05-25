#include <iostream>
#include <cmath>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int n;
    double x;

    cout << "Введите натуральное число n: ";
    cin >> n;
    cout << "Введите вещественное число x: ";
    cin >> x;

    double S = 0.0;

    for (int i = 1; i <= n; ++i) {
        double fyv = 1.0;

        for (int j = 1; j <= 2 * i; ++j) {
            fyv *= sin(j * x / (2 * i + 1));
        }

        S += fyv;
    }

    cout << "Результат выражения: " << S << endl;

    return 0;
}