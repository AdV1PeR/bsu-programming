#include <iostream>
#include <cstring>

using namespace std;

class MyString {
public:
    char value[20];
    // Конструктор по умолчанию
    MyString() {
        value[0] = '\0';
    }
    // Конструктор, принимающий C-строку
    MyString(const char* initValue) {
        strncpy(value, initValue, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
    }
    // Конструктор, принимающий символ и количество его повторений
    MyString(char ch, int count) {
        for (int i = 0; i < count && i < sizeof(value) - 1; ++i) {
            value[i] = ch;
        }
        value[count] = '\0';
    }
    // Конструктор, принимающий C-строку, количество символов и флаг
    MyString(const char* initValue, int n, bool fromStart) {
        if (fromStart) {
            strncpy(value, initValue, n);
            value[n] = '\0';
        } else {
            int len = strlen(initValue);
            if (n > len) n = len;
            strncpy(value, initValue + len - n, n);
            value[n] = '\0';
        }
    }
    // Конструктор копирования
    MyString(const MyString& other) {
        strncpy(value, other.value, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
    }
    // Конструктор перемещения
    MyString(MyString&& other) noexcept {
        strncpy(value, other.value, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
        other.value[0] = '\0';
    }

    void input() {
        cout << "Введите строку: ";
        cin.getline(value, sizeof(value));
    }

    void display() const {
        cout << "Содержимое: " << value << endl;
    }

    int ASCII_sum() const {
        int sum = 0;
        for (int i = 0; value[i] != '\0'; ++i) {
            sum += static_cast<int>(value[i]);
        }
        return sum;
    }

    MyString toUpperCase() const {
        MyString upperStr;
        for (int i = 0; value[i] != '\0'; ++i) {
            upperStr.value[i] = my_toupper(value[i]);
        }
        upperStr.value[strlen(value)] = '\0';
        return upperStr;
    }

    // Вспомогательная функция my_toupper
    char my_toupper(char ch) const {
        if (ch >= 'a' && ch <= 'z') {
            return ch - ('a' - 'A');
        }
        return ch;
    }
};

int main() {
    MyString str1, str2;
    str1.input(); str1.display();
    str2.input(); str2.display();

    char ch; int count;
    cout << "str3: "; cin >> ch; cout << "Символы str3: "; cin >> count; cin.ignore();
    MyString str3(ch, count); str3.display();

    char initValue[100]; int n;
    cout << "str4: "; cin.getline(initValue, sizeof(initValue));
    cout << "Символы str4: "; cin >> n; MyString str4(initValue, n, true); str4.display();

    cout << "str5: "; cin.ignore(); cin.getline(initValue, sizeof(initValue));
    cout << "Символы str5: "; cin >> n; MyString str5(initValue, n, false); str5.display();

    MyString str6 = str1; str6.display();
    MyString str7 = move(str2); str7.display();

    cout << "Суммарный ASCII-код: " << str1.ASCII_sum() << endl;
    MyString upperStr = str1.toUpperCase(); upperStr.display();

    return 0;
}
