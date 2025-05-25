#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    double x, y;
    bool p;

    cout << " input x, y" << endl;
    cin >> x >> y;

    p = (x <= 0 && x >= -1 && y <= 1 && y >= -1 && y >= -x - 1 && y <= x + 1);
    cout << p << endl;

    return 0;
}