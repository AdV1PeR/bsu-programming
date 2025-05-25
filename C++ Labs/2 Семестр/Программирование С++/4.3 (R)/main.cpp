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

    // Оператор присваивания
    Student& operator=(const Student& other) {
        if (this != &other) {
            strncpy(name, other.name, 99);
            name[99] = '\0';
            gender = other.gender;
            course = other.course;
            age = other.age;
            grade = other.grade;
        }
        return *this;
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

class StudentDatabase {
    Student* students;
    int count;
    int capacity;

public:
    // Конструкторы
    StudentDatabase() : students(nullptr), count(0), capacity(0) {}

    ~StudentDatabase() {
        delete[] students;
    }

    void addStudent() {
        if (count >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            Student* newStudents = new Student[newCapacity];
            for (int i = 0; i < count; ++i) {
                newStudents[i] = students[i];
            }
            delete[] students;
            students = newStudents;
            capacity = newCapacity;
        }
        students[count].inputFromKeyboard();
        count++;
    }

    void saveToBinaryFile(const char* filename) const {
        ofstream out(filename, ios::binary);
        for (int i = 0; i < count; ++i) {
            students[i].saveToBinaryFile(out);
        }
        out.close();
    }

    void loadFromBinaryFile(const char* filename) {
        ifstream in(filename, ios::binary);
        in.seekg(0, ios::end);
        int size = in.tellg() / sizeof(Student);
        in.seekg(0, ios::beg);

        delete[] students;
        students = new Student[size];
        count = size;
        Student::loadFromBinaryFile(in, students, size);
        in.close();
    }
    void print() const {
        cout << "\nДанные о студентах:" << endl;
        for (int i = 0; i < count; ++i) {
            students[i].print();
        }
    }

    void findExcellentStudents(int targetCourse) const {
        int countExcellent = 0;
        for (int i = 0; i < count; ++i) {
            if (students[i].getCourse() == targetCourse && students[i].isExcellent()) {
                countExcellent++;
            }
        }
        cout << "Количество отличников на курсе " << targetCourse << ": " << countExcellent << endl;
    }
};

int main() {
    StudentDatabase db;
    const char* filename = "data.bin";
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить студента\n";
        cout << "2. Сохранить базу данных в файл\n";
        cout << "3. Загрузить базу данных из файла\n";
        cout << "4. Вывести данные о студентах\n";
        cout << "5. Найти отличников на курсе\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice; cin.ignore();

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                db.saveToBinaryFile(filename);
                cout << "Данные сохранены в файл " << filename << endl;
                break;
            case 3:
                db.loadFromBinaryFile(filename);
                cout << "Данные загружены из файла " << filename << endl;
                break;
            case 4:
                db.print();
                break;
            case 5: {
                int targetCourse;
                cout << "Введите номер курса: ";
                cin >> targetCourse;
                db.findExcellentStudents(targetCourse);
                break;
            }
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}
