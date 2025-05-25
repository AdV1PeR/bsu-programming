#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    const int MAX = 80;
    char str1[MAX] = { 0 };
    char str2[MAX] = { 0 };
    char str3[MAX] = { 0 };
    char SOGL[] = "BbCcDdFfGgKkMmNnPpQqRrSsTtWwXxZz ";
    int k = 0;

    cout << "Введите строку: ";
    cin.getline(str1, MAX);

    for (unsigned int i = 0; i < strlen(str1); i++) {
        if (str1[i] != '*') {
            str2[k++] = str1[i];
        }
    }
    str2[k] = '\0';
    cout << "Результат1 = " << str2 << endl;

    int z = 0;

    for (int j = 0; j < strlen(SOGL); j++) {
        for (unsigned int i = 0; i < strlen(str1); i++) {
            if (str1[i] == SOGL[j]) {
                str3[z++] = SOGL[j];
                break;
            }
        }
    }
    str3[z] = '\0';
    cout << "Результат2 = " << str3 << endl;

    return 0;
}