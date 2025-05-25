#include <iostream>
#include <cstring>

using std::cout;
using std::cin;

struct Node {
    char* data;
    Node* next;
};

void queue(Node*& front, const char* word) {
    Node* newNode = new Node;
    newNode->data = new char[strlen(word) + 4];
    strcpy(newNode->data, word);
    strcat(newNode->data, "xyz");
    newNode->next = nullptr;

    if (!front) {
        front = newNode;
    } else {
        Node* current = front;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void clearQueue(Node*& front) {
    while (front) {
        delete[] front->data;
        Node* nextNode = front->next;
        delete front;
        front = nextNode;
    }
}

int main() {
    char input[1000];
    cout << "Введите строку: ";
    cin.getline(input, sizeof(input));

    Node* front = nullptr;
    for (char* token = strtok(input, " "); token; token = strtok(nullptr, " "))
        queue(front, token);

    cout << "Слова с добавленным 'xyz': ";
    for (Node* current = front; current; current = current->next)
        cout << current->data << " ";
    cout << std::endl;

    clearQueue(front);
    return 0;
}
