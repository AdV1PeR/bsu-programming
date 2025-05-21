#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

struct DataPoint {
    double x;
    double y;
    int g;
};

bool isSymmetric(istream& input, int n) {
    if (n % 2 != 0) return false;

    stack<int> groupStack;
    DataPoint point;

    for (int i = 0; i < n; ++i) {
        input >> point.x >> point.y >> point.g;
        groupStack.push(point.g);
    }

    for (int i = n; i < n; ++i) {
        input >> point.x >> point.y >> point.g;
        if (groupStack.top() != point.g) return false;
        groupStack.pop();
    }

    return true;
}

bool checkG() {
    cout << "Выберите источник данных (1 - файл, 2 - клавиатура): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string filename;
        cout << "Введите имя файла: ";
        cin >> filename;
        ifstream file(filename);
        if (!file) return false;

        int n;
        file >> n;
        return isSymmetric(file, n);
    }
    else if (choice == 2) {
        cout << "Введите количество точек: ";
        int n;
        cin >> n;
        return isSymmetric(cin, n);
    }
    return false;
}

int main() {
    cout << (checkG() ? "Yes" : "No") << endl;
    return 0;
}
