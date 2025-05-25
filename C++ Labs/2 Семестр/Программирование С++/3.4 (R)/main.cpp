#include <iostream>
#include <fstream>
#include <cstring>

using std::cin; using std::cout; using std::endl; using std::cerr;
using std::ifstream; using std::ofstream;

struct Student {
    char name[100]; // ФИО
    char gender;    // Пол
    int course;     // Курс
    int age;        // Возраст
    float grade;    // Успехи
};

void parseStudent(const char* line, Student& s) {
    char genderStr[2];
    char* token = strtok(const_cast<char*>(line), ",");
    strcpy(s.name, token); token = strtok(nullptr, ",");
    s.age = atoi(token); token = strtok(nullptr, ",");
    s.course = atoi(token); token = strtok(nullptr, ",");
    strcpy(genderStr, token); s.gender = genderStr[0];
    token = strtok(nullptr, ","); s.grade = atof(token);
}

void fillStudentFile(const char* filename) {
    ofstream oFile(filename);
    if (!oFile) {
        cerr << "ASHIBKA!" << endl;
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

        oFile << s.name << "," << s.age << "," << s.course << "," << s.gender << "," << s.grade << endl;
    }

    oFile.close();
}

void printStudents(const char* filename) {
    ifstream iFile(filename);
    if (!iFile) {
        cerr << "ASHIBKA!" << endl;
        return;
    }

    char line[256];
    while (iFile.getline(line, sizeof(line))) {
        Student s;
        parseStudent(line, s); // Используем новую функцию для парсинга
        cout << "ФИО: " << s.name << ", Возраст: " << s.age
        << ", Курс: " << s.course << ", Пол: " << s.gender
        << ", Успеваемость: " << s.grade << endl;
    }

    iFile.close();
}

int Otlichniki(const char* filename, int course) {
    ifstream iFile(filename);
    if (!iFile) {
        cerr << "ASHIBKA!" << endl;
        return 0;
    }

    char line[256];
    int count = 0;

    while (iFile.getline(line, sizeof(line))) {
        Student s;
        parseStudent(line, s);

        if (s.course == course && (s.grade >= 8)) {
            count++;
        }
    }

    iFile.close();
    return count;
}

int main() {
    const char* filename = "Students.txt";

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
