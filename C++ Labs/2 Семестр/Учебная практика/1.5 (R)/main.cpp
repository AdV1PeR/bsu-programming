#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// F(n) = F(n-1) + F(n-2)

int fib(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

int fib_iter(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void choice(int n, int method) {
    switch (method) {
        case 1:
            cout << "F(" << n << ") = " << fib(n) << endl;
            break;
        case 2:
            cout << "F(" << n << ") = " << fib_iter(n) << endl;
            break;
        default:
            cout << "Эээмм..." << endl;
            break;
    }
}

int main() {
    int n, method;
    cout << "Введите номер члена последовательности Фибоначчи: ";
    cin >> n;
    cout << "Выберите метод:\n1. Рекурсивный\n2. Итеративный\nВведите номер метода: ";
    cin >> method;

    choice(n, method);

    return 0;
}
