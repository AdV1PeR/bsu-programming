#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void manualInput(vector<int>& vec) {
    cout << "Введите " << vec.size() << " элементов: ";
    for (auto& el : vec) {
        cin >> el;
    }
}

void randomFill(vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = rand() % 10;
    }
}

void printVector(const vector<int>& vec) {
    cout << "Вектор: ";
    for (const auto& el : vec) {
        cout << el << " ";
    }
    cout << endl;
}

void inputVector(vector<int>& vec) {
    int size;
    cout << "Введите размер вектора: ";
    cin >> size;
    while (size <= 0) {
        cout << "- Еррор: ";
        cin >> size;
    }
    vec.resize(size);

    cout << "1 - Клавиатура, 2 - Рандом: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        manualInput(vec);
    } else {
        randomFill(vec);
    }

    printVector(vec);
}

vector<int> combineVectors(const vector<int>& vec1, const vector<int>& vec2) {
    vector<int> combined = vec1;
    for (const auto& el : vec2) {
        combined.push_back(el);
    }
    return combined;
}

void findMinMax(const vector<int>& combined, size_t& min_idx, size_t& max_idx) {
    if (combined.empty()) return;

    min_idx = 0;
    max_idx = 0;
    for (size_t i = 1; i < combined.size(); ++i) {
        if (combined[i] < combined[min_idx]) min_idx = i;
        if (combined[i] > combined[max_idx]) max_idx = i;
    }
}

void printResult(const vector<int>& combined, size_t min_idx, size_t max_idx) {
    vector<int> temp = combined;
    if (min_idx != max_idx) {
        swap(temp[min_idx], temp[max_idx]);
    }

    cout << "\nРезультат после обмена: ";
    for (const auto& el : temp) {
        cout << el << " ";
    }
    cout << endl;

    cout << "Поменялись местами элементы: "
    << "Минимальный элемент = " << combined[min_idx]
    << " (индекс " << min_idx << "), "
    << "Максимальный элемент = " << combined[max_idx]
    << " (индекс " << max_idx << ")." << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<int> vec1;
    inputVector(vec1);
    vector<int> vec2;
    inputVector(vec2);

    vector<int> combined = combineVectors(vec1, vec2);
    size_t min_idx, max_idx;
    findMinMax(combined, min_idx, max_idx);

    printResult(combined, min_idx, max_idx);

    return 0;
}
