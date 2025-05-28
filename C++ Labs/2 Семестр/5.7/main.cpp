#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

bool isDelimiter(char c, const string& delimiters) {
    return delimiters.find(c) != string::npos;
}

int main() {
    const string delimiters = " .,:;!?-()";

    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in.is_open() || !out.is_open()) {
        cerr << "Ошибка открытия файлов!" << endl;
        return 1;
    }

    list<string> wordsQueue;
    string currentWord;
    char c;

    while (in.get(c)) {
        if (isDelimiter(c, delimiters)) {
            if (!currentWord.empty()) {
                if (currentWord.front() == 'a') {
                    wordsQueue.push_back(currentWord);
                }
                currentWord.clear();
            }
        } else {
            currentWord += tolower(c);
        }
    }

    if (!currentWord.empty() && currentWord.front() == 'a') {
        wordsQueue.push_back(currentWord);
    }

    bool first = true;
    for (const auto& word : wordsQueue) {
        if (!first) out << " ";
        out << word;
        first = false;
    }

    in.close();
    out.close();
    return 0;
}
