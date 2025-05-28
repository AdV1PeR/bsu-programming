#include <iostream>
#include <string>

using namespace std;

string remove_punctuation(const string& word) {
    const string punct = ".,;:!?()-#";
    string cleaned;
    for (char c : word) {
        if (punct.find(c) == string::npos) {
            cleaned += c;
        }
    }
    return cleaned;
}

bool has_unique_chars(const string& word) {
    string chars;
    for (char c : word) {
        if (chars.find(c) != string::npos) {
            return false;
        }
        chars += c;
    }
    return true;
}

string process_input(const string& input) {
    string result;
    string unique_words = " ";

    size_t start = 0;
    size_t end = 0;
    while (start < input.size()) {
        while (start < input.size() && input[start] == ' ') start++;
        if (start >= input.size()) break;
        end = start;
        while (end < input.size() && input[end] != ' ') end++;
        string word = input.substr(start, end - start);
        start = end;

        string cleaned = remove_punctuation(word);
        if (cleaned.empty()) continue;

        if (!has_unique_chars(cleaned)) continue;

        string search_word = " " + cleaned + " ";
        if (unique_words.find(search_word) != string::npos) {
            continue;
        }

        if (!result.empty()) {
            result += " ";
        }
        result += cleaned;
        unique_words += cleaned + " ";
    }

    return result;
}

int main() {
    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    string output = process_input(input);
    cout << "Результат: " << output << endl;

    return 0;
}
