#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void left(int* arr, int n, int k) {
    k = k % n;
    if (k == 0) return;

    int* temp = new int[n];
    for (int i = 0; i < n; i++) { // Копируем
        temp[i] = arr[(i + k) % n]; // Сдвигаем
    }


    for (int i = 0; i < n; i++) {   // Вставляем в основной массив
        arr[i] = temp[i];
    }

    delete[] temp;
}

int main() {
    int n, k;

    cout << "Введите количество элементов массива: ";
    cin >> n;

    int* arr = new int[n]; // Динамический

    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Введите количество позиций для сдвига влево: ";
    cin >> k;

    left(arr, n, k);

    cout << "Массив после сдвига: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}
