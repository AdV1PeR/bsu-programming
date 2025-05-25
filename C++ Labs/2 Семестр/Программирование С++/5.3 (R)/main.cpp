#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <sstream>
#include <cctype>

using namespace std;

string remove_punctuation(const string& word) {
    const string punct = ".,;:!?()-#";
    string cleaned;
    copy_if(word.begin(), word.end(), back_inserter(cleaned),
        [&punct](char c) { return punct.find(c) == string::npos; });
    return cleaned;
}

bool has_unique_chars(const string& word) {
    set<char> chars;
    for (char c : word) {
        if (!chars.insert(toupper(c)).second)
            return false;
    }
    return true;
}

string process_input(const string& input) {
    istringstream iss(input);
    string word;
    set<string> unique_words;
    ostringstream result;

    while (iss >> word) {
        string cleaned = remove_punctuation(word);
        transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::toupper);

        if (!cleaned.empty() && 
            has_unique_chars(cleaned) && 
            unique_words.insert(cleaned).second) {
            
            if (result.tellp() != 0) result << ' ';
            result << cleaned;
        }
    }

    return result.str();
}

int main() {
    string input;
    cout << "Введите строку: ";
    getline(cin, input);

    string output = process_input(input);
    cout << "Результат: " << output << endl;

    return 0;
}