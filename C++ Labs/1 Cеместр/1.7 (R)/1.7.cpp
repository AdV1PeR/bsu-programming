#include <iostream>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    int queenX, queenY, bishopX, bishopY;

    cout << "Введите координаты ферзя (x, y): ";
    cin >> queenX >> queenY;
    cout << "Введите координаты слона (x, y): ";
    cin >> bishopX >> bishopY;

    bool qAb = (queenX == bishopX) || (queenY == bishopY) || (abs(queenX - bishopX) == abs(queenY - bishopY));
    bool bAq = (abs(queenX - bishopX) == abs(queenX - bishopY));

    if (qAb && bAq) {
        cout << "Ферзь и слон угрожают друг другу." << endl;
    }
    else if (bAq) {
        cout << "Ферзь бьет слона." << endl;
    }
    else if (bAq) {
        cout << "Слон бьет ферзя." << endl;
    }
    else {
        cout << "Фигуры не угрожают друг другу." << endl;
    }

    return 0;
}