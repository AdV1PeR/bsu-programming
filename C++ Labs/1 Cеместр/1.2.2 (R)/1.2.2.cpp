#include <iostream>

using namespace std;

int main() {
    
    setlocale(LC_ALL, "RU");

    double num;

    cout << "Введите положительное вещественное число: ";
    cin >> num;

    if (num <= 0) {
        cout << "Число должно быть положительным." << endl;
        return 1;
    }


    double a = num - static_cast<int>(num);

    int sum = 0;
    int count = 0;

    while (count < 5) {
        a *= 10;
        int b = static_cast<int>(a);
        sum += b;
        a -= b;
        count++;
    }

    cout << "Сумма первых пяти цифр дробной части: " << sum << endl;

    return 0;
}