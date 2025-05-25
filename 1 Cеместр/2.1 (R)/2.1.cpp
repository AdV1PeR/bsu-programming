#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите количество натуральных чисел, которые делятся на 3 и 10: ";
    cin >> n;

    int count = 0;
    int sum = 0;
    int number = 1;

    while (count < n) {
        if (number % 30 == 0) {
            sum += number;
            count++;
        }
        number++;
    }

    cout << "Сумма первых " << n << " натуральных чисел, которые делятся на 3 и 10: " << sum << endl;

    return 0;
}