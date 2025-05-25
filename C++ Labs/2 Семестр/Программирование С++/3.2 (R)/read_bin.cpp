#include <iostream>
#include <fstream>

using namespace std;

void readBinaryFile(const char* filename) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    int number;
    cout << "Содержимое файла " << filename << ":" << endl;

    // Читаем числа из файла до конца
    while (inputFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        cout << number << " ";
    }

    cout << endl;
    inputFile.close();
}

int main() {
    const char* inputFileName = "output.bin"; // Укажите имя вашего бинарного файла
    readBinaryFile(inputFileName);
    return 0;
}
