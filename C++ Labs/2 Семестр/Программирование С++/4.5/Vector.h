#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    static const int MAX_SIZE = 1000;
    double* data;
    int size;

    bool isValidIndex(int index) const;

public:
    // Конструкторы и деструктор
    Vector();
    Vector(int size);
    Vector(int size, double value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    ~Vector();

    // Операторы присваивания
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // Методы доступа
    int getSize() const;
    void setSize(int newSize);
    double getElement(int index) const;
    void setElement(int index, double value);

    // Операции с векторами
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;

    // Операции с скаляром
    Vector operator+(double scalar) const;
    Vector operator-(double scalar) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;

    // Другие методы
    double length() const;
    void print() const;
    void input();
    void fillRandom(double min, double max);
    double max() const;

    // Метод для проверки равенства размеров
    bool checkSizeEquality(const Vector& other) const; // Теперь public
};

#endif // VECTOR_H
