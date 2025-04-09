#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

class MyString {
private:
    char value[100];

public:
    MyString() {
        value[0] = '\0';
    }

    MyString(const char* initValue) {
        strncpy(value, initValue, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
    }

    MyString(char ch, int count) {
        for (int i = 0; i < count && i < sizeof(value) - 1; ++i) {
            value[i] = ch;
        }
        value[count] = '\0';
    }

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

    MyString(const MyString& other) {
        strncpy(value, other.value, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
    }

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

    int asciiSum() const {
        int sum = 0;
        for (int i = 0; value[i] != '\0'; ++i) {
            sum += static_cast<int>(value[i]);
        }
        return sum;
    }

    MyString toUpperCase() const {
        MyString upperStr;
        for (int i = 0; value[i] != '\0'; ++i) {
            upperStr.value[i] = toupper(value[i]);
        }
        upperStr.value[strlen(value)] = '\0';
        return upperStr;
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

    cout << "Суммарный ASCII-код: " << str1.asciiSum() << endl;
    MyString upperStr = str1.toUpperCase(); upperStr.display();

    return 0;
}
