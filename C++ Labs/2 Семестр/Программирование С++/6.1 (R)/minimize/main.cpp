#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <memory>

using namespace std;

class Device {
protected:
    int year;
public:
    Device(int y) : year(y) {}
    virtual ~Device() = default;
    virtual void print(ostream& os) const = 0;
};

class HDD : public Device {
    int size; // GB
    string brand;
public:
    HDD(int y, int s, string b) : Device(y), size(s), brand(move(b)) {}

    void print(ostream& os) const override {
        os << "HDD\t" << year << "\t" << size << "GB\t" << brand << "\n";
    }
};

class SSD : public Device {
    long long tbw;
    long long used;
public:
    SSD(int y, long long t, long long u) : Device(y), tbw(t), used(u) {}

    void print(ostream& os) const override {
        os << "SSD\t" << year << "\t"
        << tbw/1000000000 << "GB TBW\t"
        << (used*100/tbw) << "% used\n";
    }
};

class Monitor : public Device {
    float size; // inches
    int width;
    int height;
    int hz;
public:
    Monitor(int y, float s, int w, int h, int z)
    : Device(y), size(s), width(w), height(h), hz(z) {}

    void print(ostream& os) const override {
        os << "Monitor\t" << year << "\t"
        << size << "\"\t"
        << width << "x" << height << "\t"
        << hz << "Hz\n";
    }
};

class Processor : public Device {
    string model;
    int cores;
    float ghz;
public:
    Processor(int y, string m, int c, float g)
    : Device(y), model(move(m)), cores(c), ghz(g) {}

    void print(ostream& os) const override {
        os << "CPU\t" << year << "\t"
        << model << "\t"
        << cores << " cores\t"
        << ghz << "GHz\n";
    }
};

class Generator {
    static bool seeded;
public:
    static int rand_int(int min, int max) {
        if(!seeded) {
            srand(time(0));
            seeded = true;
        }
        return rand() % (max - min + 1) + min;
    }

    static float rand_float(float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
    }
};
bool Generator::seeded = false;

class Computer {
    vector<unique_ptr<Device>> parts; // Используем unique_ptr

public:
    Computer() = default;
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

    // Запрещаем копирование
    Computer(const Computer&) = delete;
    Computer& operator=(const Computer&) = delete;

    // Разрешаем перемещение
    Computer(Computer&&) = default;
    Computer& operator=(Computer&&) = default;
};

class Inventory {
    vector<Computer> computers;

    unique_ptr<Device> create_hdd() {
        const string brands[] = {"WD", "Seagate", "Toshiba"};
        return make_unique<HDD>(
            Generator::rand_int(2015, 2023),
                                Generator::rand_int(500, 4000),
                                brands[Generator::rand_int(0, 2)]
        );
    }

    unique_ptr<Device> create_ssd() {
        int cap = 250 * Generator::rand_int(1, 8);
        long long tbw = cap * 4000000000LL;
        return make_unique<SSD>(
            Generator::rand_int(2019, 2023),
                                tbw,
                                tbw * Generator::rand_int(100, 3500) / 1000
        );
    }

    unique_ptr<Device> create_monitor() {
        float size = Generator::rand_float(21.5, 34.0);
        int w = 1920, h = 1080;
        if(size > 24) { w = 2560; h = 1440; }
        if(size > 27) { w = 3840; h = 2160; }
        return make_unique<Monitor>(
            Generator::rand_int(2018, 2023),
                                    size,
                                    w,
                                    h,
                                    Generator::rand_int(60, 240)
        );
    }

    unique_ptr<Device> create_cpu() {
        const string models[] = {
            "i3-10100", "i5-11400", "i7-12700",
            "Ryzen 3 3100", "Ryzen 5 5600", "Ryzen 7 5800"
        };
        return make_unique<Processor>(
            Generator::rand_int(2018, 2023),
                                      models[Generator::rand_int(0, 5)],
                                      Generator::rand_int(2, 8),
                                      Generator::rand_float(2.8, 5.0)
        );
    }

public:
    void generate(int count) {
        for(int i = 0; i < count; i++) {
            Computer pc;
            pc.add_part(create_hdd());
            pc.add_part(create_ssd());
            pc.add_part(create_monitor());
            pc.add_part(create_cpu());
            computers.push_back(move(pc)); // Перемещаем объект
        }
    }

    void print_all() const {
        cout << "\n====== Inventory Report ======\n";
        for(const auto& pc : computers) {
            pc.print(cout);
        }
    }

    void save(const char* filename) {
        ofstream file(filename);
        file << "====== Inventory Report ======\n";
        for(const auto& pc : computers) {
            pc.print(file);
        }
    }
};

int main() {
    Inventory inv;
    inv.generate(3);
    inv.print_all();
    inv.save("report.txt");
    return 0;
}
