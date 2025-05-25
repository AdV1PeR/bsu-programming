#include <iostream>
#include <fstream>
#include <cstring>

using std::cin, std::cout, std::endl, std::cerr;
using std::ifstream, std::ofstream, std::ios;

struct Student {
    char name[100]; // ФИО
    char gender;    // Пол
    int course;     // Курс
    int age;        // Возраст
    float grade;    // Успехи
};

void fillStudentFile(const char* filename) {
    ofstream oFile(filename, ios::binary);
    if (!oFile) {
        cerr << "Ну и дела" << endl;
        return;
    }

    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        Student s;
        cout << "ФИО: "; cin.getline(s.name, 100);
        cout << "Возраст: "; cin >> s.age;
        cout << "Курс: "; cin >> s.course;
        cout << "Пол (M/F): "; cin >> s.gender;
        cout << "Успеваемость: "; cin >> s.grade;
        cin.ignore();

        oFile.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }

    oFile.close();
}

void printStudents(const char* filename) {
    ifstream iFile(filename, ios::binary);
    if (!iFile) {
        cerr << "Ну и дела" << endl;
        return;
    }

    Student s;
    while (iFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        cout << "ФИО: " << s.name << ", Возраст: " << s.age
        << ", Курс: " << s.course << ", Пол: " << s.gender
        << ", Успеваемость: " << s.grade << endl;
    }

    iFile.close();
}

int Otlichniki(const char* filename, int course) {
    ifstream iFile(filename, ios::binary);
    if (!iFile) {
        cerr << "Ну и дела" << endl;
        return 0;
    }

    Student s;
    int count = 0;

    while (iFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.course == course && (s.grade >= 8)) {
            count++;
        }
    }

    iFile.close();
    return count;
}

int main() {
    const char* filename = "Students.bin";

    fillStudentFile(filename);
    cout << "Данные о студентах:" << endl;
    printStudents(filename);

    int course;
    cout << "Введите номер курса: ";
    cin >> course;
    int otlichnikiCount = Otlichniki(filename, course);
    cout << "Количество отличников на курсе " << course << ": " << otlichnikiCount << endl;

    return 0;
}
