#include <fstream>
#include <stack>
#include <string>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    
    if (!input.is_open() || !output.is_open()) {
        return 1;
    }

    stack<string> words_stack;
    string word;

    while (input >> word) {
        words_stack.push(word);
    }

    bool first_word = true;
    while (!words_stack.empty()) {
        if (!first_word) {
            output << " ";
        }
        output << words_stack.top();
        words_stack.pop();
        first_word = false;
    }

    input.close();
    output.close();
    return 0;
}