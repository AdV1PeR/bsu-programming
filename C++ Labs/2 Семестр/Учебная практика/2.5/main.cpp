#include <iostream>

using std::string; using std::cin;
using std::cout; using std::endl;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;

    LinkedList() : head(nullptr) {}

    void append(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    bool contains(T value) {
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void print() {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Функция для формирования нового списка
    LinkedList<T> symmetricDifference(LinkedList<T>& other) {
        LinkedList<T> result;
        Node<T>* temp = head;

        // Элементы, которые есть в этом списке, но нет в другом
        while (temp) {
            if (!other.contains(temp->data)) {
                result.append(temp->data);
            }
            temp = temp->next;
        }

        // Элементы, которые есть в другом списке, но нет в этом
        temp = other.head;
        while (temp) {
            if (!contains(temp->data)) {
                result.append(temp->data);
            }
            temp = temp->next;
        }

        return result;
    }
};

int main() {
    LinkedList<int> list1;
    LinkedList<int> list2;

    list1.append(1);
    list1.append(2);
    list1.append(3);
    list1.append(4);

    list2.append(3);
    list2.append(4);
    list2.append(5);
    list2.append(6);

    cout << "Список 1: ";
    list1.print();
    cout << "Список 2: ";
    list2.print();

    LinkedList<int> result = list1.symmetricDifference(list2);
    cout << "Симметрическая разность: ";
    result.print();

    return 0;
}
