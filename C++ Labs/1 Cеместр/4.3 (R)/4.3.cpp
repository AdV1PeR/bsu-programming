#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    const string prepinaniya = " .,;:!?()-#";
    string words[100];
    int wordCount = 0;
    string word;

    stringstream enter(input);
    while (enter >> word) { // Удаление разделителей
        word.erase(remove_if(word.begin(), word.end(), [&](char c) {
            return prepinaniya.find(c) != string::npos; }), 
            word.end());

        // Уникальность?
        set<char> charSet(word.begin(), word.end());
        if (charSet.size() == word.size()) {

            // Дубликаты?
            bool isDuplicate = false;
            for (int i = 0; i < wordCount; ++i) {
                if (words[i] == word) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate && wordCount < 100) {
                words[wordCount++] = word;
            }
        }
    }

    string result;
    for (int i = 0; i < wordCount; ++i) {
        result += words[i] + " ";
    }

    cout << "Результат: " << result << endl;

    return 0;
}
