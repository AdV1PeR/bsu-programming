#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout, std::cin, std::endl;

void nearSmallRight(int arr[], int n, int ans[]) {
    int stack[n];
    int top = -1;

    for (int i = n - 1; i >= 0; --i) {
        while (top != -1 && arr[stack[top]] >= arr[i]) {
            top--;
        }
        if (top != -1) {
            ans[i] = stack[top];
        } else {
            ans[i] = -1;
        }
        stack[++top] = i;
    }
}

void nearSmallLeft(int arr[], int n, int ans[]) {
    int stack[n];
    int top = -1;

    for (int i = 0; i < n; ++i) {
        while (top != -1 && arr[stack[top]] >= arr[i]) {
            top--;
        }
        if (top != -1) {
            ans[i] = stack[top];
        } else {
            ans[i] = -1;
        }
        stack[++top] = i;
    }
}

int main() {
    int n; cout << "Размер: "; cin >> n;
    int arr[n], nearRight[n], nearLeft[n];

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10;
    } cout << "Массив: ";

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    } cout << endl;

    nearSmallRight(arr, n, nearRight);
    nearSmallLeft(arr, n, nearLeft);

    int index; cout << "Индекс: "; cin >> index;

    if (index < 0 || index >= n) {
        cout << "Ну дела..." << endl;
    } else {
        int leftIndex = nearLeft[index];
        int rightIndex = nearRight[index];

        cout << "Справа: " 
             << (rightIndex != -1 ? arr[rightIndex] : -1) << " ";
        cout << endl;

        cout << "Слева: " 
             << (leftIndex != -1 ? arr[leftIndex] : -1) << " ";
        cout << endl;
    }

    return 0;
}
