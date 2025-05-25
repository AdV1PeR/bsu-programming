#include <algorithm>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {

    setlocale(LC_ALL, "RU");

    string input;
    set<char> vowels;

    cout << "Введите строку: ";
    getline(cin, input);

    string vowel = "aeiouAEIOU";

    for (char vow : input) {
        if (vowel.find(vow) != string::npos) {
            vowels.insert(vow);
        }
    }

    cout << "Гласные буквы в алфавитном порядке: ";
    for (char vowel : vowels) {
        cout << vowel << " ";
        cout << endl;
    }

    return 0;
}
