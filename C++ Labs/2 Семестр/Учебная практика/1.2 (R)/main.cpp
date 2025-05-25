#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

void CountPolynomial(double x, int n, double& result);

int main()
{
    double x0 = 1, xm = 2, dx = 0.2;
    double y = 0;
    int n;

    cout << "Введите значение n: ";
    cin >> n;

    for (double x = x0; x <= xm; x += dx)
    {
        y = 0;
        CountPolynomial(x, n, y);
        cout << "x = " << x << ", y = " << y << endl;
    }

    return 0;
}

void CountPolynomial(double x, int n, double& result)
{
    double coefficients[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    result = (9 - n) * pow(x, n);

    for (int j = 0; j < 9; j++)
    {
        result += coefficients[j] * pow(x, 7 - j);
    }
}
