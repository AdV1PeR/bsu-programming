#include <iostream>
#include <cmath>

using namespace std;

bool isPositive(double number) {
    return number > 0;
}

int digits(double number) {
    double fractionPart = number - static_cast<int>(number);
    int sum = 0;
    int count = 0;

    // +5
    while (count < 5) {
        fractionPart *= 10;
        int digit = static_cast<int>(fractionPart);
        sum += digit;
        fractionPart -= digit;
        count++;
    }

    return sum;
}

// С указателем
void pointer(double number, int* sum) {
    *sum = digits(number);
}

// С ссылкой
void reference(double number, int& sum) {
    sum = digits(number);
}

int main() {
    setlocale(LC_ALL, "RU");

    double number;

    cout << "Введите положительное вещественное число: ";
    cin >> number;

    if (!isPositive(number)) {
        cout << "Ошибка: число должно быть положительным." << endl;
        return 1;
    }

    int sum = 0;
    
    pointer(number, &sum);

    cout << "Сумма первых пяти цифр дробной части: " << sum << endl;

    return 0;
}