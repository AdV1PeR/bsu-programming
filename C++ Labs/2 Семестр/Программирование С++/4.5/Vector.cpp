#include "Vector.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using std::cin, std::cout, std::endl, std::cerr;

// Конструкторы
Vector::Vector() : size(0), data(nullptr) {}

Vector::Vector(int size) : size(size) {
    if (size < 0 || size > MAX_SIZE) {
        cerr << "Некорректный размер вектора" << endl;
        data = nullptr;
        this->size = 0;
        return;
    }
    data = new double[size]();
}

Vector::Vector(int size, double value) : size(size) {
    if (size < 0 || size > MAX_SIZE) {
        cerr << "Некорректный размер вектора" << endl;
        data = nullptr;
        this->size = 0;
        return;
    }
    data = new double[size];
    for (int i = 0; i < size; ++i) data[i] = value;
}

Vector::Vector(const Vector& other) : size(other.size) {
    data = new double[size];
    for (int i = 0; i < size; ++i) data[i] = other.data[i];
}

// Конструктор перемещения
Vector::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr; // Обнуляем указатель в перемещаемом объекте
    other.size = 0; // Обнуляем размер в перемещаемом объекте
}

// Деструктор
Vector::~Vector() {
    delete[] data;
}

// Операторы присваивания
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new double[size];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }
    return *this;
}

// Оператор присваивания перемещения
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data; // Освобождаем текущие ресурсы
        data = other.data; // Перемещаем данные
        size = other.size; // Перемещаем размер
        other.data = nullptr; // Обнуляем указатель в перемещаемом объекте
        other.size = 0; // Обнуляем размер в перемещаемом объекте
    }
    return *this;
}

// Методы доступа
int Vector::getSize() const {
    return size;
}

void Vector::setSize(int newSize) {
    if (newSize < 0 || newSize > MAX_SIZE) {
        cerr << "Некорректный размер вектора" << endl;
        return;
    }
    if (newSize == size) return;

    double* newData = new double[newSize]();
    int minSize = size < newSize ? size : newSize;
    for (int i = 0; i < minSize; ++i) newData[i] = data[i];

    delete[] data;
    data = newData;
    size = newSize;
}

bool Vector::isValidIndex(int index) const {
    return (index >= 0 && index < size);
}

double Vector::getElement(int index) const {
    if (!isValidIndex(index)) {
        cerr << "Индекс вне диапазона" << endl;
        return 0.0;
    }
    return data[index];
}

void Vector::setElement(int index, double value) {
    if (!isValidIndex(index)) {
        cerr << "Индекс вне диапазона" << endl;
        return;
    }
    data[index] = value;
}

bool Vector::checkSizeEquality(const Vector& other) const {
    if (size != other.size) {
        cerr << "Векторы должны быть одинакового размера!" << endl;
        return false;
    }
    return true;
}

// Операции с векторами
Vector Vector::operator+(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) result.data[i] = data[i] + other.data[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) result.data[i] = data[i] - other.data[i];
    return result;
}

Vector Vector::operator*(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) result.data[i] = data[i] * other.data[i];
    return result;
}

Vector Vector::operator/(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (other.data[i] == 0.0) {
            cerr << "Деление на ноль!" << endl;
            return *this;
        }
        result.data[i] = data[i] / other.data[i];
    }
    return result;
}

// Операции с скаляром
Vector Vector::operator+(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] + scalar;
    }
    return result;
}

Vector Vector::operator-(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] - scalar;
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

Vector Vector::operator/(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (scalar == 0.0) {
            cerr << "Деление на ноль!" << endl;
            return *this;
        }
        result.data[i] = data[i] / scalar;
    }
    return result;
}

// Другие методы
double Vector::length() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += data[i] * data[i];
    return sqrt(sum);
}

void Vector::print() const {
    cout << "[ ";
    for (int i = 0; i < size; ++i) cout << data[i] << (i < size - 1 ? ", " : " ");
    cout << "]" << endl;
}

void Vector::input() {
    for (int i = 0; i < size; ++i) {
        cout << "Элемент " << i << ": ";
        cin >> data[i];
    }
}

void Vector::fillRandom(double min, double max) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < size; ++i) {
        data[i] = min + (max - min) * (rand() / (double)RAND_MAX);
    }
}

double Vector::max() const {
    if (size == 0) {
        cerr << "Вектор пуст" << endl;
        return std::numeric_limits<double>::lowest(); // Return the lowest possible value
    }
    double maxVal = data[0];
    for (int i = 1; i < size; ++i) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }
    return maxVal;
}
