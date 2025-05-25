#include <iostream>
#include <fstream>

using std::cout, std::cerr, std::endl;
using std::ofstream, std::ifstream;

const char* I = "i.txt";
const char* O = "o.txt";

int main() {
    ifstream i_f(I);
    ofstream o_f(O);

    if (!i_f.is_open() || !o_f.is_open()) {
        cerr << "еррор, ЕРРОР!" << endl;
        return 1;
    }

    int currentN;
    int lastN = 0;
    bool lastPair = false;

    while (i_f >> currentN) {
        bool currentPair = (currentN % 2 == 0);

        if (currentPair != lastPair) {
            o_f << currentN << " ";
            lastN = currentN;
            lastPair = currentPair;
        }
    }

    i_f.close();
    o_f.close();

    return 0;
}
