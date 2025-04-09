#include <iostream>

using std::cin, std::cout, std::cerr, std::endl;

bool goraArr(int arr[], int n) {
    if (n < 3) {
        return false;
    }

    int i = 0;
    while (i < n - 1 && arr[i] < arr[i + 1]) {
        i++;
    }

    if (i == 0 || i == n - 1) {
        return false;
    }

    while (i < n - 1 && arr[i] > arr[i + 1]) {
        i++;
    }

    return i == n - 1;
}

int main() {
    int arrSize;
    cout << "Размер: ";
    cin >> arrSize;

    if (arrSize < 3) {
        cerr << "Error!" << endl;
        return 1;
    }

    int* arr = new int[arrSize];
    cout << "Элементы: ";
    for (int i = 0; i < arrSize; i++) {
        cin >> arr[i];
    }

    if (goraArr(arr, arrSize)) {
        cout << "Массив горный" << endl;
    } else {
        cout << "Массив не горный" << endl;
    }

    delete[] arr;
    return 0;
}
