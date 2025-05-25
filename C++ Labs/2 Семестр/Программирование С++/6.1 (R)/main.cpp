#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <iomanip>
#include <tuple>

using namespace std;

// Базовый класс устройства
class Device {
protected:
    int year;
public:
    Device(int year) : year(year) {}
    virtual ~Device() = default;
    virtual void printInfo(ostream& os) const = 0;
    virtual string type() const = 0;
};

// Конкретные класссы устройств
class HDD : public Device {
    int capacity;    // в GB
    string manufacturer;
public:
    HDD(int y, int c, string m) : Device(y), capacity(c), manufacturer(move(m)) {}

    void printInfo(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << setw(5) << capacity << "GB"
        << " | " << manufacturer << "\n";
    }

    string type() const override { return "HDD"; }
};

class SSD : public Device {
    long long tbw;       // Total Bytes Written
    long long written;   // Фактически записано
public:
    SSD(int y, long long t, long long w) : Device(y), tbw(t), written(w) {}

    void printInfo(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << fixed << setprecision(2) << (tbw/1e12) << "TBW"
        << " | " << setw(6) << (written*100.0/tbw) << "% used"
        << "\n";
    }

    string type() const override { return "SSD"; }
};

class Monitor : public Device {
    float diagonal;  // в дюймах
    int width;
    int height;
    int refresh;     // в Hz
public:
    Monitor(int y, float d, int w, int h, int r)
    : Device(y), diagonal(d), width(w), height(h), refresh(r) {}

    void printInfo(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << fixed << setprecision(1) << diagonal << "\""
        << " | " << width << "x" << height
        << " | " << refresh << "Hz\n";
    }

    string type() const override { return "Monitor"; }
};

class Processor : public Device {
    string model;
    int cores;
    float frequency; // в GHz
public:
    Processor(int y, string m, int c, float f)
    : Device(y), model(move(m)), cores(c), frequency(f) {}

    void printInfo(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << setw(15) << model
        << " | " << cores << " cores"
        << " | " << fixed << setprecision(2) << frequency << "GHz\n";
    }

    string type() const override { return "CPU"; }
};

// Генератор случайных значений
class RandomGenerator {
    static mt19937 gen;
public:
    static void init() { gen.seed(time(nullptr)); }

    static int rand_int(int min, int max) {
        return uniform_int_distribution<>(min, max)(gen);
    }

    static float rand_float(float min, float max) {
        return uniform_real_distribution<float>(min, max)(gen);
    }

    template<typename T>
    static const T& rand_element(const vector<T>& items) {
        return items[rand_int(0, items.size()-1)];
    }
};
mt19937 RandomGenerator::gen;

// Фабрика устройств
class DeviceFactory {
public:
    static unique_ptr<Device> create_hdd() {
        static vector<string> makers = {"WD", "Seagate", "Toshiba", "Hitachi"};
        return make_unique<HDD>(
            RandomGenerator::rand_int(2015, 2023),
                                RandomGenerator::rand_int(500, 16000),
                                RandomGenerator::rand_element(makers)
        );
    }

    static unique_ptr<Device> create_ssd() {
        static vector<string> makers = {"Samsung", "Crucial", "Kingston", "WD"};
        int capacity = 250 * RandomGenerator::rand_int(1, 16);
        long long tbw = capacity * 750'000'000LL;
        return make_unique<SSD>(
            RandomGenerator::rand_int(2019, 2023),
                                tbw,
                                tbw * RandomGenerator::rand_float(0.01, 0.9)
        );
    }

    static unique_ptr<Device> create_monitor() {
        static vector<string> brands = {"Dell", "LG", "Samsung", "ASUS"};
        float diag = RandomGenerator::rand_float(21.5, 34.0);
        auto [w, h] = generate_resolution(diag);
        return make_unique<Monitor>(
            RandomGenerator::rand_int(2018, 2023),
                                    diag,
                                    w,
                                    h,
                                    generate_refresh_rate(diag)
        );
    }

    static unique_ptr<Device> create_processor() {
        static vector<tuple<string, int, float>> models = {
            {"Intel i3", 4, 3.6}, {"Intel i5", 6, 4.2},
            {"Intel i7", 8, 4.7}, {"AMD Ryzen 3", 4, 3.8},
            {"AMD Ryzen 5", 6, 4.4}, {"AMD Ryzen 7", 8, 4.8}
        };
        auto [model, cores, freq] = RandomGenerator::rand_element(models);
        return make_unique<Processor>(
            RandomGenerator::rand_int(2018, 2023),
                                      model,
                                      cores,
                                      freq + RandomGenerator::rand_float(-0.3, 0.5)
        );
    }

private:
    static pair<int, int> generate_resolution(float diag) {
        if(diag < 24) return {1920, 1080};
        if(diag < 28) return {2560, 1440};
        return {3840, 2160};
    }

    static int generate_refresh_rate(float diag) {
        return diag < 27 ? RandomGenerator::rand_int(60, 165)
        : RandomGenerator::rand_int(60, 240);
    }
};

// Класс компьютера
class Computer {
    vector<unique_ptr<Device>> parts;

public:
    Computer() = default; // Добавляем конструктор по умолчанию

    void add_part(unique_ptr<Device> part) {
        parts.push_back(move(part));
    }

    void print(ostream& os) const {
        os << "\n---------- Computer ----------\n";
        for(const auto& part : parts) {
            part->print(os);
        }
        os << "-----------------------------\n";
    }

    Computer(const Computer&) = delete;
    Computer& operator=(const Computer&) = delete;

    Computer(Computer&&) = default;
    Computer& operator=(Computer&&) = default;
};

// Система инвентаризации
class InventorySystem {
    vector<Computer> computers;

public:
    void generate(int count) {
        for(int i = 0; i < count; ++i) {
            Computer pc;
            pc.add(DeviceFactory::create_hdd());
            pc.add(DeviceFactory::create_ssd());
            pc.add(DeviceFactory::create_monitor());
            pc.add(DeviceFactory::create_processor());
            computers.push_back(move(pc));
        }
    }

    void report(ostream& os) const {
        os << "          COMPUTER INVENTORY REPORT\n"
        << "          =========================\n\n";

        for(size_t i = 0; i < computers.size(); ++i) {
            computers[i].print(os, i+1);
        }
    }

    void save(const string& filename) const {
        ofstream file(filename);
        if(file) report(file);
    }
};

int main() {
    RandomGenerator::init();
    InventorySystem inventory;

    // Генерация 5 компьютеров
    inventory.generate(5);

    // Вывод в консоль
    inventory.report(cout);

    // Сохранение в файл
    inventory.save("inventory_report.txt");
    cout << "\nReport saved to inventory_report.txt\n";

    return 0;
}
