#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

struct Node {
    char* word;
    Node* next;
};

// Создание нового узла стека
Node* createNode(const char* word) {
    Node* newNode = new Node;
    newNode->word = new char[strlen(word) + 1];
    strcpy(newNode->word, word);
    newNode->next = nullptr;
    return newNode;
}

// Добавление слова в стек
void push(Node*& top, const char* word) {
    Node* newNode = createNode(word);
    newNode->next = top;
    top = newNode;
}

// Удаление верхнего элемента стека
void pop(Node*& top) {
    if (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete[] temp->word;
        delete temp;
    }
}

// Пуст ли стек
bool isEmpty(Node* top) {
    return top == nullptr;
}

// Получение верхнего элемента стека
const char* pik(Node* top) {
    return top != nullptr ? top->word : nullptr;
}

void print(const char* str) {
    Node* stack = nullptr; // Инициализация стека

    const char* delimiters = " .,;:!?()-";
    char* token = strtok(const_cast<char*>(str), delimiters);

    while (token != nullptr) {
        push(stack, token);
        token = strtok(nullptr, delimiters);
    }

    while (!isEmpty(stack)) {
        cout << pik(stack) << " ";
        pop(stack);
    }
}

int main() {
    char input[1000];

    cout << "Введите строку: ";
    cin.getline(input, 1000);

    print(input);
    cout << endl;
    return 0;
}
