// Do-While

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    double x0 = 1.0, xn = 5.0, dx = 0.5, a = 2.5;
    double x = x0;

    cout << setw(10) << "x" << setw(15) << "ω(x)" << setw(10) << "Branch" << endl;

    do {
        double q;
        int w;

        if (x > a) {
            q = pow(x, 3);
            w = 1;
        }
        else if (x == a) {
            q = x * sin(a * x);
            w = 2;
        }
        else {
            q = exp(a * x) * cos(a * x);
            w = 3;
        }

        cout << setw(10) << x << setw(15) << q << setw(10) << w << endl;
        x += dx;
    } while (x <= xn);

    return 0;
}   