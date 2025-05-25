#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    const unsigned short int MAX = 65535;
    unsigned int short count = 0;

    for (unsigned int num = 2; num <= MAX; ++num) {
        bool a = true;

        for (unsigned short int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                a = false;
                break;
            }
        }

        if (a) {
            count++;
        }
    }

    cout << "Количество простых чисел в диапазоне от 0 до " << MAX << ": " << count << endl;

    return 0;
}
