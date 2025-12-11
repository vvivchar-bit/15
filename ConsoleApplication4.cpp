#include <iostream>
#include <string>
#include <vector>

// ------------------------ 1. Ієрархія House – CampusBuilding ------------------------

class House {
protected:
    std::string address;
    double area;   // загальна площа
    int floors;

public:
    House(const std::string& addr, double ar, int fl)
        : address(addr), area(ar), floors(fl) {
    }

    virtual ~House() = default;

    virtual void printInfo() const {
        std::cout << "House at: " << address
            << "\n  Area: " << area
            << " m^2\n  Floors: " << floors << "\n";
    }
};

class CampusBuilding : public House {
    std::string faculty;
    int classrooms;

public:
    CampusBuilding(const std::string& addr, double ar, int fl,
        const std::string& fac, int rooms)
        : House(addr, ar, fl), faculty(fac), classrooms(rooms) {
    }

    void printInfo() const override {
        std::cout << "Campus building (faculty: " << faculty << ")\n"
            << "  Address: " << address
            << "\n  Area: " << area << " m^2"
            << "\n  Floors: " << floors
            << "\n  Classrooms: " << classrooms << "\n";
    }
};

// ------------------------ 2. Ієрархія DigitalDevice – MobilePhone ------------------------

class DigitalDevice {
protected:
    std::string brand;
    std::string model;
    double power; // умовно, споживана потужність

public:
    DigitalDevice(const std::string& br, const std::string& md, double pw)
        : brand(br), model(md), power(pw) {
    }

    virtual ~DigitalDevice() = default;

    virtual void printInfo() const {
        std::cout << "Digital device: " << brand << " " << model
            << "\n  Power: " << power << " W\n";
    }
};

class MobilePhone : public DigitalDevice {
    std::string os;
    double screenSize;
    int simCount;

public:
    MobilePhone(const std::string& br, const std::string& md, double pw,
        const std::string& osName, double screen, int sims)
        : DigitalDevice(br, md, pw),
        os(osName), screenSize(screen), simCount(sims) {
    }

    void printInfo() const override {
        std::cout << "Mobile phone: " << brand << " " << model
            << "\n  OS: " << os
            << "\n  Screen: " << screenSize << "''"
            << "\n  SIM slots: " << simCount
            << "\n  Power: " << power << " W\n";
    }
};

// ------------------------ 3. Шаблонна функція пошуку в діапазоні ------------------------

template <typename T>
std::vector<T> findInRange(const T* arr, std::size_t size,
    const T& low, const T& high) {
    std::vector<T> result;
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] >= low && arr[i] <= high) {
            result.push_back(arr[i]);
        }
    }
    return result;
}

// ------------------------ 4. Шаблон класу Pair ------------------------

template <typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;

public:
    Pair(const T1& a, const T2& b) : first(a), second(b) {}

    const T1& getFirst() const { return first; }
    const T2& getSecond() const { return second; }

    void print() const {
        std::cout << "(" << first << ", " << second << ")";
    }
};

// ------------------------ Демонстрація роботи в main() -----------------------------------

int main() {
    std::cout << "=== House / CampusBuilding demo ===\n";

    House h1("Shevchenka 10", 120.5, 2);
    CampusBuilding c1("Universytetska 1", 3500.0, 5, "Computer Science", 40);
    CampusBuilding c2("Universytetska 3", 4200.0, 6, "Electronics", 55);

    House* buildings[3];
    buildings[0] = &h1;
    buildings[1] = &c1;
    buildings[2] = &c2;

    for (House* b : buildings) {
        b->printInfo();
        std::cout << "---------------------------\n";
    }

    std::cout << "\n=== DigitalDevice / MobilePhone demo ===\n";

    DigitalDevice d1("HP", "LaserJet 1020", 350);
    MobilePhone m1("Samsung", "Galaxy S24", 15, "Android", 6.7, 2);
    MobilePhone m2("Apple", "iPhone 15", 18, "iOS", 6.1, 1);

    DigitalDevice* devices[3];
    devices[0] = &d1;
    devices[1] = &m1;
    devices[2] = &m2;

    for (DigitalDevice* dev : devices) {
        dev->printInfo();
        std::cout << "---------------------------\n";
    }

    std::cout << "\n=== Template function findInRange demo ===\n";

    int intArr[] = { 1, 5, 10, 15, 20, 25 };
    double dblArr[] = { 1.2, 3.5, 7.7, 10.0, 12.5 };
    std::string strArr[] = { "apple", "banana", "cherry", "plum", "watermelon" };

    auto intsInRange = findInRange(intArr, 6, 5, 20);
    auto dblInRange = findInRange(dblArr, 5, 3.0, 11.0);
    auto strInRange = findInRange(strArr, 5, std::string("b"), std::string("p"));

    std::cout << "Integers in [5;20]: ";
    for (int x : intsInRange) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Doubles in [3.0;11.0]: ";
    for (double x : dblInRange) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Strings in [\"b\"; \"p\"] (lexicographical): ";
    for (const auto& s : strInRange) std::cout << s << " ";
    std::cout << "\n";

    std::cout << "\n=== Template Pair demo ===\n";

    Pair<int, double> p1(10, 3.14);
    Pair<std::string, int> p2("students", 25);

    std::cout << "p1 = ";
    p1.print();
    std::cout << "\n";

    std::cout << "p2 = ";
    p2.print();
    std::cout << "\n";

    return 0;
}
