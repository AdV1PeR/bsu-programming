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
    ofstream oFile(filename);
    if (!oFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    cin.ignore(); // Игнорируем символ новой строки после ввода числа

    for (int i = 0; i < n; ++i) {
        Student s;
        cout << "ФИО: "; cin.getline(s.name, 100);
        cout << "Возраст: "; cin >> s.age;
        cout << "Курс: "; cin >> s.course;
        cout << "Пол (M/F): "; cin >> s.gender;
        cout << "Успеваемость: "; cin >> s.grade;
        cin.ignore(); // Игнорируем символ новой строки после ввода

        oFile << s.name << "," << s.age << "," << s.course << "," << s.gender << "," << s.grade << endl;
    }

    oFile.close();
}

void printStudents(const vector<Student>& students) {
    cout << setw(35) << left << "ФИО"
    << setw(5) << "Возраст "
    << setw(5) << "Курс "
    << setw(5) << "Пол "
    << setw(10) << "Успеваемость " << endl;
    cout << string(60, '-') << endl;

    for (const auto& s : students) {
        cout << setw(35) << left << s.name
        << setw(5) << s.age
        << setw(5) << s.course
        << setw(5) << s.gender
        << setw(10) << fixed << setprecision(2) << s.grade << endl;
    }
}
void writeStudentsToFile(const char* filename, const vector<Student>& students) {
    ofstream oFile(filename);
    if (!oFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    // Запись заголовков
    oFile << left << setw(35) << "ФИО"
    << setw(5) << "Возраст "
    << setw(5) << "Курс "
    << setw(5) << "Пол "
    << setw(10) << "Успеваемость " << endl;
    oFile << string(60, '-') << endl; // Разделительная линия

    // Запись данных студентов
    for (const auto& s : students) {
        oFile << left << setw(35) << s.name
        << setw(5) << s.age
        << setw(5) << s.course
        << setw(5) << s.gender
        << setw(10) << fixed << setprecision(2) << s.grade << endl;
    }

    oFile.close();
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

void loadStudentsFromFile(const char* filename, vector<Student>& students) {
    ifstream iFile(filename);
    if (!iFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    char line[256];
    while (iFile.getline(line, sizeof(line))) {
        Student s;
        char* token = strtok(line, ",");
        strcpy(s.name, token); token = strtok(nullptr, ",");
        s.age = atoi(token); token = strtok(nullptr, ",");
        s.course = atoi(token); token = strtok(nullptr, ",");
        s.gender = token[0]; token = strtok(nullptr, ",");
        s.grade = atof(token);
        students.push_back(s);
    }

    iFile.close();
}

int main() {
    const char* filename = "BetterStudents.txt";
    fillStudentFile(filename); // Заполнение файла данными о студентах

    vector<Student> students;
    loadStudentsFromFile(filename, students); // Загрузка студентов из файла

    sort(students.begin(), students.end(), compareByCourse); // Сортировка студентов по курсу

    cout << "Отсортированный список студентов по курсу:" << endl;
    printStudents(students); // Вывод отсортированного списка студентов

    // Запись отсортированных студентов в новый файл
    writeStudentsToFile("SortedStudents.txt", students);

    int course;
    cout << "Введите номер курса для подсчета отличников: ";
    cin >> course;
    int otlichnikiCount = Otlichniki(students, course); // Подсчет отличников на указанном курсе
    cout << "Количество отличников на курсе " << course << ": " << otlichnikiCount << endl;

    return 0;
}
