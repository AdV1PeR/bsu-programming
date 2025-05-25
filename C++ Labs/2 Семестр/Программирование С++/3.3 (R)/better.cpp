#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

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
        cerr << "ASHIBKA!" << endl;
        return;
    }

    int n;
    cout << "Введите количество студентов: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Student s;
        cout << "ФИО: "; cin.ignore(); cin.getline(s.name, 100);
        cout << "Возраст: "; cin >> s.age;
        cout << "Курс: "; cin >> s.course;
        cout << "Пол (M/F): "; cin >> s.gender;
        cout << "Успеваемость: "; cin >> s.grade;
        oFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    }

    oFile.close();
}

void printStudents(const vector<Student>& students) {
    for (const auto& s : students) {
        cout << setw(35) << s.name
        << setw(5) << s.age
        << setw(5) << s.course
        << setw(5) << s.gender
        << setw(5) << fixed << setprecision(2) << s.grade << endl;
    }
}

int Otlichniki(const vector<Student>& students, int course) {
    int count = 0;
    for (const auto& s : students) {
        if (s.course == course && (s.grade >= 8)) {
            count++;
        }
    }
    return count;
}

bool compareByCourse(const Student& a, const Student& b) {
    return a.course < b.course;
}

int main() {
    const char* filename = "BetterStudents.bin";
    fillStudentFile(filename);
    ifstream iFile(filename, ios::binary);

    vector<Student> students;
    Student s;
    while (iFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        students.push_back(s);
    }
    iFile.close();

    sort(students.begin(), students.end(), compareByCourse);

    cout << "Отсортированный список студентов по курсу:" << endl;
    printStudents(students);

    int course;
    cout << "Введите номер курса для подсчета отличников: ";
    cin >> course;
    int otlichnikiCount = Otlichniki(students, course);
    cout << "Количество отличников на курсе " << course << ": " << otlichnikiCount << endl;

    return 0;
}
