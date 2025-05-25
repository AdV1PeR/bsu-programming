#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

const int MAX_WORDS = 100;

// Удаление разделителей
string cleanWord(const string& word, const string& delimiters) {
    string cleanedWord = word;
    cleanedWord.erase(remove_if(cleanedWord.begin(), cleanedWord.end(), [&](char c) {
        return delimiters.find(c) != string::npos;
        }), cleanedWord.end());
    return cleanedWord;
}

// Уникальность?
bool hasUniqueCharacters(const string& word) {
    set<char> charSet(word.begin(), word.end());
    return charSet.size() == word.size();
}

// Извлечение
void extractUniqueWords(const string& input, string words[], int& wordCount) {
    const string delimiters = " .,;:!?()-";
    stringstream ss(input);
    string word;

    while (ss >> word) {
        string cleanedWord = cleanWord(word, delimiters);
        if (hasUniqueCharacters(cleanedWord)) { // Проверка на дубликаты
            bool isDuplicate = false;
            for (int i = 0; i < wordCount; ++i) {
                if (words[i] == cleanedWord) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate && wordCount < MAX_WORDS) {
                words[wordCount++] = cleanedWord;
            }
        }
    }
}

void printResult(const string words[], int wordCount) {
    string result;
    for (int i = 0; i < wordCount; ++i) {
        result += words[i] + " ";
    }
    cout << "Результат: " << result << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    string words[MAX_WORDS];
    int wordCount = 0;

    extractUniqueWords(input, words, wordCount);
    printResult(words, wordCount);

    return 0;
}