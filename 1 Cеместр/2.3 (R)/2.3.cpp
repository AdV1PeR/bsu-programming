#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int n, m;
    cout << "Введите натуральное число n, m: ";
    cin >> n >> m;  

    int maxD = 0;
    int nWMD = n;

    for (int i = n; i <= m; ++i) {
            int count = 0;

        for (int j = 1; j <= i; ++j) {
            if (i % j == 0) {
                count++;
            }
        }

        if (count > maxD) {
            maxD = count;
            nWMD = i;
        }
    }

    cout << "Число с наибольшим кол-вом делителей в диапазоне [" << n << ", " << m << "] = " << nWMD << endl;
    cout << "Кол-во делителей: " << maxD << endl;

    return 0;
}