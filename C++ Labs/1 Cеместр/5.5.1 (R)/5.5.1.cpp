#include <algorithm>
#include <iostream>
#include <string>
#include <set>

using namespace std;

set<char> extractVowels(const string& input) {
    set<char> vowels;
    string vowel = "aeiouAEIOU";

    for (char ch : input) {
        if (vowel.find(ch) != string::npos) {
            vowels.insert(ch);
        }
    }

    return vowels;
}

void printVowels(const set<char>& vowels) {
    cout << "Гласные буквы в алфавитном порядке: ";
    for (char vowel : vowels) {
        cout << vowel << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    string input;
    cout << "Введите строку: ";
    getline(cin, input);
    set<char> vowels = extractVowels(input);
    printVowels(vowels);

    return 0;
}