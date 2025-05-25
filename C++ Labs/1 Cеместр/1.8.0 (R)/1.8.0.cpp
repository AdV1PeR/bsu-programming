#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int a, b, c;

    cout << "Введите значение a, b, c: ";
    cin >> a >> b >> c;

    int r = a ^ b;
    int f = r | c;

    cout << "Результат (a (+) b) + c = " << f << endl;

    return 0;
}