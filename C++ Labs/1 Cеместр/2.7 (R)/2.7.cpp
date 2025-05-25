#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите значение n: ";
    cin >> n;

    double sum = 0.0;
    double product = 1.0;
    double a;

    for (int i = 0; i < n; ++i) {
        cout << "Введите значение a" << (i + 1) << ": ";
        cin >> a;
        product *= (a + (i - 1));
        sum += 1.0 / product;
    }

    cout << "Результат: " << sum << endl;

    return 0;
}