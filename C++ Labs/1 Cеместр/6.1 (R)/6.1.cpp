#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_SUBJECTS = 10;

struct Student {
    string fullName;            // ФИО
    int age;                    // Возраст
    int course;                 // Курс
    char gender;                // Пол
    int grades[MAX_SUBJECTS];   // Успеваемость (оценки по предметам)
    int numSubjects;            // Количество предметов
};

// Заполнение информации о студентах
void fillStudentsInfo(Student students[], int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        cout << "Введите ФИО студента " << (i + 1) << ": ";
        getline(cin >> ws, students[i].fullName);
        cout << "Введите возраст: ";
        cin >> students[i].age;
        cout << "Введите курс: ";
        cin >> students[i].course;
        cout << "Введите пол (M/F): ";
        cin >> students[i].gender;

        // Успеваемость
        cout << "Введите количество предметов (макс. " << MAX_SUBJECTS << "): ";
        cin >> students[i].numSubjects; // Сохраняем количество предметов
        for (int j = 0; j < students[i].numSubjects; ++j) {
            cout << "Введите оценку по предмету " << (j + 1) << ": ";
            cin >> students[i].grades[j];
        }
    }
}

void printStudents(const Student students[], int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        cout << "ФИО: " << students[i].fullName << ", Возраст: " << students[i].age
            << ", Курс: " << students[i].course << ", Пол: " << students[i].gender
            << ", Успеваемость: ";
        for (int j = 0; j < students[i].numSubjects; ++j) { // Используем numSubjects
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

// Подсчет неуспевающих студентов
int countFailingStudents(const Student students[], int numStudents, int course, int subjectIndex, int passingGrade) {
    int count = 0;
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].course == course && students[i].grades[subjectIndex] < passingGrade) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "RU");

    int numStudents;
    cout << "Введите количество студентов (макс. " << MAX_STUDENTS << "): ";
    cin >> numStudents;

    if (numStudents > MAX_STUDENTS) {
        cout << "Превышено максимальное количество студентов!" << endl;
        return 1;
    }

    Student students[MAX_STUDENTS];
    fillStudentsInfo(students, numStudents);
    printStudents(students, numStudents);

    int course, subjectIndex, passingGrade;
    cout << "Введите курс для проверки: ";
    cin >> course;
    cout << "Введите индекс предмета (0 для первого, 1 для второго и т.д.): ";
    cin >> subjectIndex;
    cout << "Введите проходную оценку: ";
    cin >> passingGrade;

    int failingCount = countFailingStudents(students, numStudents, course, subjectIndex, passingGrade);
    cout << "Количество неуспевающих студентов на курсе " << course << ": " << failingCount << endl;

    return 0;
}