#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

class PhoneBook {
private:
    unordered_map<string, string> nameToPhone;
    unordered_map<string, string> phoneToName;

public:
    bool addContact(const string& name, const string& phone) {
        if (nameToPhone.count(name)) {
            cout << "Абонент '" << name << "' уже существует\n";
            return false;
        }
        if (phoneToName.count(phone)) {
            cout << "Номер '" << phone << "' уже зарегистрирован\n";
            return false;
        }

        nameToPhone[name] = phone;
        phoneToName[phone] = name;
        cout << "Добавлен: " << name << " - " << phone << endl;
        return true;
    }

    void searchByName(const string& name) {
        auto it = nameToPhone.find(name);
        if (it != nameToPhone.end()) {
            cout << "Найден: " << name << " | Телефон: " << it->second << endl;
        } else {
            cout << "Абонент '" << name << "' не найден\n";
        }
    }

    void searchByPhone(const string& phone) {
        auto it = phoneToName.find(phone);
        if (it != phoneToName.end()) {
            cout << "Найден: " << it->second << " | Телефон: " << phone << endl;
        } else {
            cout << "Номер '" << phone << "' не найден\n";
        }
    }

    bool deleteContact(const string& key) {
        if (nameToPhone.count(key)) {
            string phone = nameToPhone[key];
            nameToPhone.erase(key);
            phoneToName.erase(phone);
            cout << "Удален: " << key << endl;
            return true;
        }

        if (phoneToName.count(key)) {
            string name = phoneToName[key];
            phoneToName.erase(key);
            nameToPhone.erase(name);
            cout << "Удален: " << key << endl;
            return true;
        }

        cout << "Контакт '" << key << "' не найден\n";
        return false;
    }

    void showAll() const {
        if (nameToPhone.empty()) {
            cout << "Телефонная книга пуста\n";
            return;
        }

        cout << "\nВсе контакты (" << nameToPhone.size() << "):\n";
        for (const auto& [name, phone] : nameToPhone) {
            cout << "▸ " << name << " - " << phone << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка сохранения файла\n";
            return;
        }

        for (const auto& [name, phone] : nameToPhone) {
            file << name << "," << phone << "\n";
        }
        cout << "Сохранено в '" << filename << "' (" << nameToPhone.size() << " записей)\n";
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка чтения файла\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string name = line.substr(0, pos);
                string phone = line.substr(pos+1);
                addContact(name, phone);
            }
        }
        cout << "Загружено из '" << filename << "'\n";
    }
};

int main() {
    PhoneBook pb;
    string command;

    cout << "Телефонная книгаn\n";
    cout << "Команды:\n"
         << "  add [имя] [телефон]  - добавить\n"
         << "  del [ключ]           - удалить\n"
         << "  findn [имя]          - найти по имени\n"
         << "  findp [телефон]      - найти по телефону\n"
         << "  list                 - список всех\n"
         << "  save [файл]          - сохранить\n"
         << "  load [файл]          - загрузить\n"
         << "  exit                 - выход\n";

    while (true) {
        cout << "\n> ";
        cin >> command;

        if (command == "add") {
            string name, phone;
            cin >> name >> phone;
            pb.addContact(name, phone);
        }
        else if (command == "del") {
            string key;
            cin >> key;
            pb.deleteContact(key);
        }
        else if (command == "findn") {
            string name;
            cin >> name;
            pb.searchByName(name);
        }
        else if (command == "findp") {
            string phone;
            cin >> phone;
            pb.searchByPhone(phone);
        }
        else if (command == "list") {
            pb.showAll();
        }
        else if (command == "save") {
            string filename;
            cin >> filename;
            pb.saveToFile(filename);
        }
        else if (command == "load") {
            string filename;
            cin >> filename;
            pb.loadFromFile(filename);
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
