#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <iomanip>
#include <tuple>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <functional>
#include <typeinfo>

using namespace std;

class Device {
protected:
    int year;

    void validate_year(int y) {
        if(y < 1980 || y > 2024)
            throw invalid_argument("Invalid year: " + to_string(y));
    }

public:
    Device(int year) : year(year) {
        validate_year(year);
    }
    virtual ~Device() = default;
    virtual void print(ostream& os) const = 0;
    virtual string type() const = 0;
    virtual void save(ofstream& file) const = 0;
    virtual bool matches(const Device& other) const = 0;
};

class HDD : public Device {
    int capacity;
    string manufacturer;

public:
    HDD(int y, int c, string m) : Device(y), capacity(c), manufacturer(move(m)) {
        if(capacity <= 0) throw invalid_argument("HDD capacity must be positive");
        if(manufacturer.empty()) throw invalid_argument("Manufacturer cannot be empty");
    }

    void print(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << setw(5) << capacity << "GB"
        << " | " << manufacturer << "\n";
    }

    void save(ofstream& file) const override {
        file << "HDD " << year << " " << capacity << " " << manufacturer << "\n";
    }

    string type() const override { return "HDD"; }

    bool matches(const Device& other) const override {
        if(typeid(*this) != typeid(other)) return false;
        const auto& o = static_cast<const HDD&>(other);
        return (year == o.year || o.year == -1) &&
        (capacity == o.capacity || o.capacity == -1) &&
        (manufacturer == o.manufacturer || o.manufacturer.empty());
    }
};

class SSD : public Device {
    long long tbw;
    long long written;

public:
    SSD(int y, long long t, long long w) : Device(y), tbw(t), written(w) {
        if(tbw <= 0) throw invalid_argument("TBW must be positive");
        if(written < 0 || written > tbw)
            throw invalid_argument("Invalid written bytes value");
    }

    void print(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << fixed << setprecision(2) << (tbw/1e12) << "TBW"
        << " | " << setw(6) << fixed << setprecision(2)
        << (written*100.0/tbw) << "% used"
        << "\n";
    }

    void save(ofstream& file) const override {
        file << "SSD " << year << " " << tbw << " " << written << "\n";
    }

    string type() const override { return "SSD"; }

    bool matches(const Device& other) const override {
        if(typeid(*this) != typeid(other)) return false;
        const auto& o = static_cast<const SSD&>(other);
        return (year == o.year || o.year == -1) &&
        (tbw == o.tbw || o.tbw == -1) &&
        (written == o.written || o.written == -1);
    }
};

class Monitor : public Device {
    float diagonal;
    int width;
    int height;
    int refresh;

public:
    Monitor(int y, float d, int w, int h, int r)
    : Device(y), diagonal(d), width(w), height(h), refresh(r) {
        if(diagonal <= 0) throw invalid_argument("Diagonal must be positive");
        if(width <= 0 || height <= 0) throw invalid_argument("Invalid resolution");
        if(refresh <= 0) throw invalid_argument("Refresh rate must be positive");
    }

    void print(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << fixed << setprecision(1) << diagonal << "\""
        << " | " << width << "x" << height
        << " | " << refresh << "Hz\n";
    }

    void save(ofstream& file) const override {
        file << "MON " << year << " " << diagonal << " "
        << width << " " << height << " " << refresh << "\n";
    }

    string type() const override { return "Monitor"; }

    bool matches(const Device& other) const override {
        if(typeid(*this) != typeid(other)) return false;
        const auto& o = static_cast<const Monitor&>(other);
        return (year == o.year || o.year == -1) &&
        (diagonal == o.diagonal || o.diagonal == -1) &&
        (width == o.width || o.width == -1) &&
        (height == o.height || o.height == -1) &&
        (refresh == o.refresh || o.refresh == -1);
    }
};

class Processor : public Device {
    string model;
    int cores;
    float frequency;

public:
    Processor(int y, string m, int c, float f)
    : Device(y), model(move(m)), cores(c), frequency(f) {
        if(cores <= 0) throw invalid_argument("Core count must be positive");
        if(frequency <= 0) throw invalid_argument("Frequency must be positive");
        if(model.empty()) throw invalid_argument("Model cannot be empty");
    }

    void print(ostream& os) const override {
        os << left << setw(9) << type()
        << " | " << setw(4) << year
        << " | " << setw(15) << model
        << " | " << cores << " cores"
        << " | " << fixed << setprecision(2) << frequency << "GHz\n";
    }

    void save(ofstream& file) const override {
        file << "CPU " << year << " " << model << " "
        << cores << " " << frequency << "\n";
    }

    string type() const override { return "CPU"; }

    bool matches(const Device& other) const override {
        if(typeid(*this) != typeid(other)) return false;
        const auto& o = static_cast<const Processor&>(other);
        return (year == o.year || o.year == -1) &&
        (model == o.model || o.model.empty()) &&
        (cores == o.cores || o.cores == -1) &&
        (frequency == o.frequency || o.frequency == -1);
    }
};

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

class DeviceFactory {
public:
    static unique_ptr<Device> create_from_string(const string& data) {
        istringstream iss(data);
        string type;
        iss >> type;

        if(type == "HDD") {
            int y = -1, c = -1;
            string m;
            iss >> y >> c;
            getline(iss >> ws, m);
            return make_unique<HDD>(y, c, m);
        }
        if(type == "SSD") {
            int y = -1;
            long long t = -1, w = -1;
            iss >> y >> t >> w;
            return make_unique<SSD>(y, t, w);
        }
        if(type == "MON") {
            int y = -1, w = -1, h = -1, r = -1;
            float d = -1;
            iss >> y >> d >> w >> h >> r;
            return make_unique<Monitor>(y, d, w, h, r);
        }
        if(type == "CPU") {
            int y = -1, c = -1;
            float f = -1;
            string m;
            iss >> y;
            getline(iss >> ws, m, ';');
            iss >> c >> f;
            return make_unique<Processor>(y, m, c, f);
        }
        throw invalid_argument("Unknown device type");
    }

    static unique_ptr<Device> create_random_hdd() {
        static vector<string> makers = {"WD", "Seagate", "Toshiba", "Hitachi"};
        return make_unique<HDD>(
            RandomGenerator::rand_int(2015, 2023),
                                RandomGenerator::rand_int(500, 16000),
                                RandomGenerator::rand_element(makers)
        );
    }

    static unique_ptr<Device> create_random_ssd() {
        int capacity = 250 * RandomGenerator::rand_int(1, 16);
        long long tbw = capacity * 750'000'000LL;
        return make_unique<SSD>(
            RandomGenerator::rand_int(2019, 2023),
                                tbw,
                                tbw * RandomGenerator::rand_float(0.01, 0.9)
        );
    }

    static unique_ptr<Device> create_random_monitor() {
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

    static unique_ptr<Device> create_random_processor() {
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

class Computer {
    vector<unique_ptr<Device>> parts;

public:
    void add(unique_ptr<Device> part) {
        parts.push_back(move(part));
    }

    void print(ostream& os) const {
        os << "\n---------- Computer ----------\n";
        for(const auto& part : parts) {
            part->print(os);
        }
        os << "-----------------------------\n";
    }

    void save(ofstream& file) const {
        for(const auto& part : parts) {
            part->save(file);
        }
        file << "END\n";
    }

    static Computer load(ifstream& file) {
        Computer pc;
        string line;
        while(getline(file, line)) {
            if(line == "END") break;
            pc.add(DeviceFactory::create_from_string(line));
        }
        return pc;
    }

    vector<Device*> get_devices() const {
        vector<Device*> result;
        for(const auto& p : parts) {
            result.push_back(p.get());
        }
        return result;
    }
};

class InventorySystem {
    vector<Computer> computers;

public:
    void add_computer(Computer pc) {
        computers.push_back(move(pc));
    }

    void generate_random() {
        Computer pc;
        pc.add(DeviceFactory::create_random_hdd());
        pc.add(DeviceFactory::create_random_ssd());
        pc.add(DeviceFactory::create_random_monitor());
        pc.add(DeviceFactory::create_random_processor());
        computers.push_back(move(pc));
    }

    void report(ostream& os) const {
        os << "          COMPUTER INVENTORY REPORT\n"
        << "          =========================\n\n";

        for(size_t i = 0; i < computers.size(); ++i) {
            computers[i].print(os);
        }
    }

    void save(const string& filename) const {
        ofstream file(filename);
        if(file) {
            for(const auto& pc : computers) {
                pc.save(file);
            }
        }
    }

    void load(const string& filename) {
        ifstream file(filename);
        if(file) {
            computers.clear();
            Computer pc;
            string line;
            while(getline(file, line)) {
                if(line == "END") {
                    computers.push_back(move(pc));
                    pc = Computer();
                }
                else {
                    pc.add(DeviceFactory::create_from_string(line));
                }
            }
        }
    }

    void search_devices(const string& query) const {
        try {
            auto target = DeviceFactory::create_from_string(query);
            cout << "\nSearch results for [" << query << "]:\n";

            for(const auto& computer : computers) {
                for(const auto& device : computer.get_devices()) {
                    if(device->type() == target->type() &&
                        device->matches(*target))
                    {
                        device->print(cout);
                    }
                }
            }
        }
        catch(const exception& e) {
            cerr << "Search error: " << e.what() << endl;
        }
    }
};

void print_menu() {
    cout << "\n======== Inventory System ========\n"
    << "1. Add manual computer\n"
    << "2. Add random computer\n"
    << "3. Save to file\n"
    << "4. Load from file\n"
    << "5. Show report\n"
    << "6. Search devices\n"
    << "7. Exit\n"
    << "==================================\n"
    << "Select option: ";
}

unique_ptr<Device> input_device(const string& prompt) {
    cout << prompt << " (or type 'random' to generate): ";
    string input;
    getline(cin, input);

    if(input == "random") {
        return nullptr;
    }

    try {
        return DeviceFactory::create_from_string(input);
    }
    catch(const exception& e) {
        cerr << "Error: " << e.what() << ". Try again.\n";
        return input_device(prompt);
    }
}

Computer create_manual_computer() {
    Computer pc;
    vector<string> prompts = {
        "Enter HDD (year capacity manufacturer):",
        "Enter SSD (year TBW written):",
        "Enter Monitor (year diagonal width height refresh):",
        "Enter CPU (year model cores frequency):"
    };

    for(const auto& prompt : prompts) {
        while(true) {
            auto device = input_device(prompt);
            if(!device) {
                static vector<function<unique_ptr<Device>()>> generators = {
                    &DeviceFactory::create_random_hdd,
                    &DeviceFactory::create_random_ssd,
                    &DeviceFactory::create_random_monitor,
                    &DeviceFactory::create_random_processor
                };
                device = generators[&prompt - &prompts[0]]();
            }

            try {
                pc.add(move(device));
                break;
            }
            catch(const exception& e) {
                cerr << "Error: " << e.what() << "\n";
            }
        }
    }
    return pc;
}

int main() {
    RandomGenerator::init();
    InventorySystem inventory;

    while(true) {
        print_menu();
        int choice;
        cin >> choice;
        cin.ignore();

        try {
            switch(choice) {
                case 1: {
                    Computer pc = create_manual_computer();
                    inventory.add_computer(move(pc));
                    cout << "Computer added successfully!\n";
                    break;
                }
                case 2:
                    inventory.generate_random();
                    cout << "Random computer generated!\n";
                    break;
                case 3: {
                    cout << "Enter filename: ";
                    string filename;
                    getline(cin, filename);
                    inventory.save(filename);
                    cout << "Inventory saved!\n";
                    break;
                }
                case 4: {
                    cout << "Enter filename: ";
                    string filename;
                    getline(cin, filename);
                    inventory.load(filename);
                    cout << "Inventory loaded!\n";
                    break;
                }
                case 5:
                    inventory.report(cout);
                    break;
                case 6: {
                    cout << "Enter search query (use -1 for any value):\n"
                    << "Format examples:\n"
                    << "HDD [year] [capacity] [manufacturer]\n"
                    << "SSD [year] [TBW] [written]\n"
                    << "MON [year] [diagonal] [width] [height] [refresh]\n"
                    << "CPU [year] [model] [cores] [frequency]\n"
                    << "> ";
                    string query;
                    getline(cin, query);
                    inventory.search_devices(query);
                    break;
                }
                case 7:
                    return 0;
                default:
                    cout << "Invalid choice!\n";
            }
        }
        catch(const exception& e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }
}
