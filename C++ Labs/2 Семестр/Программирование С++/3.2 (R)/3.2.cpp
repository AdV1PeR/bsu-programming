#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void inputToFile(const char* f_n) {
    ofstream o_f(f_n, ios::binary);
    if (!o_f.is_open()) {
        cerr << "Ашибка!" << endl;
        return;
    }

    int number;
    cout << "Введите числа (404 = break):" << endl;

    while (true) {
        cin >> number;
        if (number == 404) {
            break;
        }
        o_f.write(reinterpret_cast<char*>(&number), sizeof(number));
    }

    o_f.close();
}

int main() {
    const char* i_fn = "i.bin";
    const char* o_fn = "o.bin";

    inputToFile(i_fn);

    ifstream i_f(i_fn, ios::binary);
    ofstream o_f(o_fn, ios::binary);

    if (!i_f.is_open() || !o_f.is_open()) {
        cerr << "Ашибка!" << endl;
        return 1;
    }

    int currentN;
    int lastN = 0;
    bool lastPair = false;
    bool isFirstN = true;

    while (i_f.read(reinterpret_cast<char*>(&currentN), sizeof(currentN))) {
        bool currentPair = (currentN % 2 == 0);

        if (isFirstN || currentPair != lastPair) {
            o_f.write(reinterpret_cast<char*>(&currentN), sizeof(currentN));
            lastN = currentN;
            lastPair = currentPair;
            isFirstN = false;
        }
    }

    i_f.close();
    o_f.close();

    return 0;
}
