#include "Vector.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using std::cin, std::cout, std::endl, std::cerr;

Vector::Vector() : size(0), data(nullptr) {}

Vector::Vector(int size) : size(size) {
    if (size < 0 || size > MAX_SIZE) {
        cerr << "Ошибка: Недопустимый размер вектора\n";
        this->size = 0;
        data = nullptr;
        return;
    }
    data = new double[size]();
}

Vector::Vector(int size, double value) : size(size) {
    if (size < 0 || size > MAX_SIZE) {
        cerr << "Ошибка: Недопустимый размер вектора\n";
        this->size = 0;
        data = nullptr;
        return;
    }
    data = new double[size];
    for (int i = 0; i < size; ++i) {
        data[i] = value;
    }
}

Vector::Vector(const Vector& other) : size(other.size) {
    data = new double[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Vector::Vector(Vector&& other) noexcept : size(other.size), data(other.data) {
    other.size = 0;
    other.data = nullptr;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new double[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}


Vector::~Vector() {
    delete[] data;
}


int Vector::getSize() const {
    return size;
}

void Vector::setSize(int newSize) {
    if (newSize < 0 || newSize > MAX_SIZE) {
        cerr << "Ошибка: Недопустимый размер вектора\n";
        return;
    }

    if (newSize == size) return;

    double* newData = new double[newSize];
    int minSize = (newSize < size) ? newSize : size;

    for (int i = 0; i < minSize; ++i) {
        newData[i] = data[i];
    }

    for (int i = minSize; i < newSize; ++i) {
        newData[i] = 0.0;
    }

    delete[] data;
    data = newData;
    size = newSize;
}

double Vector::getElement(int index) const {
    if (index < 0 || index >= size) {
        cerr << "Ошибка: Индекс за пределами диапазона\n";
        return 0.0;
    }
    return data[index];
}

void Vector::setElement(int index, double value) {
    if (index < 0 || index >= size) {
        cerr << "Ошибка: Индекс за пределами диапазона\n";
        return;
    }
    data[index] = value;
}

bool Vector::checkSizeEquality(const Vector& other) const {
    if (size != other.size) {
        cerr << "Ошибка: Векторы должны быть одного размера\n";
        return false;
    }
    return true;
}

Vector Vector::operator+(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

Vector Vector::operator*(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

Vector Vector::operator/(const Vector& other) const {
    if (!checkSizeEquality(other)) return *this;
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        if (other.data[i] == 0.0) {
            cerr << "Ошибка: Деление на ноль\n";
            return *this;
        }
        result.data[i] = data[i] / other.data[i];
    }
    return result;
}

Vector Vector::scalarOperation(double scalar, char operation) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        switch (operation) {
            case '+':
                result.data[i] = data[i] + scalar;
                break;
            case '-':
                result.data[i] = data[i] - scalar;
                break;
            case '*':
                result.data[i] = data[i] * scalar;
                break;
            case '/':
                if (scalar == 0.0) {
                    cerr << "Ошибка: Деление на ноль\n";
                    return *this;
                }
                result.data[i] = data[i] / scalar;
                break;
        }
    }
    return result;
}


Vector Vector::operator+(double scalar) const {
    return scalarOperation(scalar, '+');
}

Vector Vector::operator-(double scalar) const {
    return scalarOperation(scalar, '-');
}

Vector Vector::operator*(double scalar) const {
    return scalarOperation(scalar, '*');
}

Vector Vector::operator/(double scalar) const {
    return scalarOperation(scalar, '/');
}


double Vector::length() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i] * data[i];
    }
    return sqrt(sum);
}

void Vector::print() const {
    cout << "[ ";
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

void Vector::input() {
    for (int i = 0; i < size; ++i) {
        cout << "Введите элемент " << i << ": ";
        cin >> data[i];
    }
}

double randDouble(double min, double max) {
    double normalized = static_cast<double>(rand()) / RAND_MAX;
    return min + normalized * (max - min);
}

void Vector::fillRandom(double min, double max) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    for (int i = 0; i < size; ++i) {
        data[i] = randDouble(min, max);
    }
}

double Vector::max() const {
    if (size == 0) {
        cerr << "Ошибка: Вектор пуст\n";
        return 0.0;
    }

    double maxVal = data[0];
    for (int i = 1; i < size; ++i) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }
    return maxVal;
}

bool Vector::isValidIndex(int index) const {
    return (index >= 0 && index < size);
}
