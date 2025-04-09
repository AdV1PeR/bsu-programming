#include <iostream>
#include <fstream>
#include <cstring>

using std::cin, std::cout, std::endl, std::cerr;
using std::ifstream, std::ofstream, std::ios;

class Student {
    char name[100];
    char gender;
    int course;
    int age;
    float grade;

public:
    // Конструкторы
    Student() : gender(' '), course(0), age(0), grade(0.0) {
        memset(name, 0, sizeof(name));
    }

    Student(const char* n, char g, int c, int a, float gr) : gender(g), course(c), age(a), grade(gr) {
        strncpy(name, n, 99);
        name[99] = '\0';
    }

    Student(const Student& other) { // Копирования
        strncpy(name, other.name, 99);
        name[99] = '\0';
        gender = other.gender;
        course = other.course;
        age = other.age;
        grade = other.grade;
    }

    Student(Student&& other) noexcept { // Перемещения
        strncpy(name, other.name, 99);
        name[99] = '\0';
        gender = other.gender;
        course = other.course;
        age = other.age;
        grade = other.grade;
        memset(other.name, 0, sizeof(other.name));
        other.gender = ' ';
        other.course = 0;
        other.age = 0;
        other.grade = 0;
    }

    ~Student() = default;

    // Методы класса
    void inputFromKeyboard() {
        cout << "ФИО: "; cin.getline(name, 100);
        cout << "Возраст: "; cin >> age;
        cout << "Курс: "; cin >> course;
        cout << "Пол (M/F): "; cin >> gender;
        cout << "Успеваемость: "; cin >> grade; cin.ignore();
    }

    void saveToBinaryFile(ofstream& file) const {
        file.write(reinterpret_cast<const char*>(this), sizeof(Student));
    }

    static void loadFromBinaryFile(ifstream& file, Student* arr, int size) {
        for(int i = 0; i < size; ++i)
            file.read(reinterpret_cast<char*>(&arr[i]), sizeof(Student));
    }

    void print() const {
        cout << "ФИО: " << name
             << ", Возраст: " << age
             << ", Курс: " << course
             << ", Пол: " << gender
             << ", Успеваемость: " << grade << endl;
    }

    bool isExcellent() const {
        return grade >= 8.0;
    }

    int getCourse() const { return course; }
};

int main() {
    const char* filename = "students.bin";
    int n = 0;

    // Ввод данных
    cout << "Введите количество студентов: "; cin >> n; cin.ignore();
    Student* students = new Student[n];
    for (int i = 0; i < n; ++i) students[i].inputFromKeyboard();

    // Сохранение в файл
    ofstream out(filename, ios::binary);
    for (int i = 0; i < n; ++i) students[i].saveToBinaryFile(out);
    out.close();
    delete[] students;

    // Загрузка из файла
    ifstream in(filename, ios::binary);
    int loadedCount = in.seekg(0, ios::end).tellg() / sizeof(Student);
    in.seekg(0, ios::beg);
    Student* loadedStudents = new Student[loadedCount];
    Student::loadFromBinaryFile(in, loadedStudents, loadedCount);
    in.close();

    // Вывод данных
    cout << "\nДанные о студентах:" << endl;
    for (int i = 0; i < loadedCount; ++i) loadedStudents[i].print();

    // Поиск отличников
    int targetCourse;
    cout << "\nВведите номер курса: "; cin >> targetCourse;
    int count = 0;
    for (int i = 0; i < loadedCount; ++i)
        if (loadedStudents[i].getCourse() == targetCourse && loadedStudents[i].isExcellent()) count++;

        cout << "Количество отличников на курсе " << targetCourse << ": " << count;

    delete[] loadedStudents;
    return 0;
}
