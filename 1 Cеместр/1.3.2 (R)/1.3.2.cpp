#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    bool a, b, c, d;

    cout << "Введите значения a, b, c, d: ";
    cin >> a >> b >> c >> d;

    bool T = !(!a || b || c) || !d;      // T = !(!a + b + c) + !d
    bool S = (a && !(b || c)) || d;      // S = a · !(b + c) + d
    bool equal = (T == S);               // T = S

    cout << "Результат T = " << T << endl;
    cout << "Результат S = " << S << endl;
    cout << "T равно S: " << (equal ? "Да" : "Нет") << endl;

    return 0;
}