#include <iostream>
#include <string>

using namespace std;

bool isVowel(char c) {
    const string vowels = "aeiouAEIOU";
    return vowels.find(c) != string::npos;
}

string getSortedVowels(const string& input) {
    string uniqueVowels;
    for (char c : input) {
        if (isVowel(c) && uniqueVowels.find(c) == string::npos) {
            uniqueVowels.append(1, c);
        }
    }

    for (size_t i = 0; i < uniqueVowels.size(); ++i) {
        for (size_t j = i + 1; j < uniqueVowels.size(); ++j) {
            if (tolower(uniqueVowels.at(i)) > tolower(uniqueVowels.at(j))) {
                swap(uniqueVowels[i], uniqueVowels[j]);
            }
        }
    }
    return uniqueVowels;
}

int main() {
    string input;
    cout << "Введите строку: ";
    getline(cin, input);
    string result = getSortedVowels(input);
    cout << "Гласные буквы в алфавитном порядке: ";
    for (char c : result) {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}
