#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>

class Staff {
protected:
    std::string name;
    int id;
    double basic;
    double daRate;
public:
    Staff(const std::string& n, int i, double b, double da = 0.42)
        : name(n), id(i), basic(b), daRate(da) {}
    virtual double pay() const = 0;
    virtual void display() const {
        std::cout << name << " (" << id << "): " << pay() << '\n';
    }
    virtual ~Staff() = default;
};

class Professor : public Staff {
    double researchAllowance;
public:
    Professor(const std::string& n, int i, double b, double research)
        : Staff(n, i, b), researchAllowance(research) {}
    double pay() const override { return basic + basic * daRate + researchAllowance; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(const std::string& n, int i, double b) : Staff(n, i, b) {}
    double pay() const override { return basic + basic * daRate; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Staff(n, i, 0.0), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

class Address {
    std::string city;
    int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Course {
    std::string title;
public:
    explicit Course(const std::string& t) : title(t) {}
    std::string getTitle() const { return title; }
};

class Person {
protected:
    std::string name;
    int id;
    std::string phone;
    Address address;
public:
    Person(const std::string& n, int i, const std::string& ph, const Address& a)
        : name(n), id(i), phone(ph), address(a) {
        std::cout << "Person constructed\n";
    }
    virtual ~Person() { std::cout << "Person destroyed\n"; }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;
    Course course;
public:
    Student(const std::string& n, int i, const std::string& ph, const Address& a,
            const std::string& prog, double gpa, const Course& c)
        : Person(n, i, ph, a), programme(prog), cgpa(gpa), course(c) {
        std::cout << "Student constructed\n";
    }
    ~Student() override { std::cout << "Student destroyed\n"; }
};

class StaffMember : virtual public Person {
protected:
    std::string department;
    double salary;
public:
    StaffMember(const std::string& n, int i, const std::string& ph, const Address& a,
                const std::string& dept, double sal)
        : Person(n, i, ph, a), department(dept), salary(sal) {
        std::cout << "Staff constructed\n";
    }
    ~StaffMember() override { std::cout << "Staff destroyed\n"; }
};

class TeachingAssistant : public Student, public StaffMember {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& ph,
                      const Address& a, const std::string& prog, double gpa,
                      const Course& c, const std::string& dept, double sal)
        : Person(n, i, ph, a), Student(n, i, ph, a, prog, gpa, c),
          StaffMember(n, i, ph, a, dept, sal) {
        std::cout << "TeachingAssistant constructed\n";
    }
    ~TeachingAssistant() override { std::cout << "TeachingAssistant destroyed\n"; }
};

class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(const std::string& n, int i, const std::string& ph,
                    const Address& a, const std::string& prog, double gpa,
                    const Course& c, double f)
        : Person(n, i, ph, a), Student(n, i, ph, a, prog, gpa, c), fellowship(f) {}
};

class InitializerListStudent : public Person {
    long long regNo;
    Address home;
public:
    InitializerListStudent(const std::string& n, int a, long long r,
                           const std::string& city, int pin)
        : Person(n, a, "", Address(city, pin)), regNo(r), home(city, pin) {}
    void print() const {
        std::cout << regNo << ' ' << name << " (" << id << ") " << home.str() << '\n';
    }
};

class Account {
public:
    virtual double vrate() const { return 3.5; }
    virtual ~Account() = default;
};

class SeniorAccount : public Account {
    std::vector<double> history;
public:
    SeniorAccount() : history(100, 0.0) {}
    double vrate() const override { return 4.0; }
    ~SeniorAccount() override = default;
};

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0.0;
public:
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }
    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }
    double total() const {
        double t = 0.0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100.0 - discount) / 100.0;
    }
};

class Vehicle {
protected:
    std::string registration;
    double dailyRate;
    bool rented = false;
    int rentedDays = 0;
public:
    Vehicle(const std::string& reg, double rate) : registration(reg), dailyRate(rate) {}
    virtual double charge(int days) const = 0;
    virtual std::string type() const = 0;
    bool rent(int days) {
        if (rented || days <= 0) return false;
        rented = true;
        rentedDays = days;
        return true;
    }
    double returnVehicle(int actualDays) {
        if (!rented || actualDays < 0) return 0.0;
        const int lateDays = std::max(0, actualDays - rentedDays);
        const double amount = charge(rentedDays) + lateDays * dailyRate * 1.25;
        rented = false;
        rentedDays = 0;
        return amount;
    }
    const std::string& getRegistration() const { return registration; }
    virtual ~Vehicle() = default;
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& r, double rate) : Vehicle(r, rate) {}
    double charge(int days) const override { return dailyRate * days; }
    std::string type() const override { return "Bicycle"; }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    std::string serviceDueDate;
public:
    MotorVehicle(const std::string& r, double rate, double level, const std::string& due)
        : Vehicle(r, rate), fuelOrChargeLevel(level), serviceDueDate(due) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& r, double rate, double fuel, const std::string& due)
        : MotorVehicle(r, rate, fuel, due) {}
    double charge(int days) const override { return dailyRate * days; }
    std::string type() const override { return "TwoWheeler"; }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;
public:
    Car(const std::string& r, double rate, double fuel, const std::string& due, int seats)
        : MotorVehicle(r, rate, fuel, due), seatingCapacity(seats) {}
    double charge(int days) const override { return dailyRate * days; }
    std::string type() const override { return "Car"; }
};

class ElectricCar : public Car {
    double batteryCapacity;
    double kWhRate;
public:
    ElectricCar(const std::string& r, double rate, double level, const std::string& due,
                int seats, double battery, double unitRate)
        : Car(r, rate, level, due, seats), batteryCapacity(battery), kWhRate(unitRate) {}
    double charge(int days) const override {
        return dailyRate * days + batteryCapacity * kWhRate;
    }
    std::string type() const override { return "ElectricCar"; }
};

class ElectricBus : public Vehicle {
    int seats;
    double batteryCapacity;
    double kWhRate;
public:
    ElectricBus(const std::string& r, double rate, int s, double battery, double unitRate)
        : Vehicle(r, rate), seats(s), batteryCapacity(battery), kWhRate(unitRate) {}
    double charge(int days) const override {
        return dailyRate * days + batteryCapacity * kWhRate;
    }
    std::string type() const override { return "ElectricBus"; }
};

void task1Demo() {
    std::cout << "\nTASK 1 - STAFF PAY\n";
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Meera", 103, 20, 1000));
    for (const auto& s : staff) s->display();
}

void task2And3Demo() {
    std::cout << "\nTASKS 2 AND 3 - VIRTUAL DIAMOND\n";
    Address a("Salem", 636001);
    Course c("Object Oriented Programming");
    {
        TeachingAssistant ta("Kavya", 201, "9876543210", a, "CSE", 8.7, c,
                             "Computer Science", 45000);
    }
    InitializerListStudent s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();
}

void task4Demo() {
    std::cout << "\nTASK 4 - POLYMORPHIC ACCOUNTS\n";
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts) std::cout << account->vrate() << '\n';
}

void task5Demo() {
    std::cout << "\nTASK 5 - CART AND THIS POINTER\n";
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c;
    p->add("Oil", 180);
    std::cout << std::fixed << std::setprecision(2) << p->total() << '\n';
    Cart second;
    Cart& ref = second;
    ref.add("Milk", 40);
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Bread", 35);
    std::cout << "Reference total: " << ref.total()
              << ", dynamic total: " << dynamicCart->total() << '\n';
    delete dynamicCart;
}

void task6Demo() {
    std::cout << "\nTASK 6 - VEHICLE RENTAL\n";
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BIC-101", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TW-201", 250, 80, "2027-01-01"));
    fleet.push_back(std::make_unique<Car>("CAR-301", 1500, 70, "2027-02-01", 5));
    fleet.push_back(std::make_unique<ElectricCar>("EV-401", 1800, 90, "2027-03-01",
                                                  5, 60, 8));
    fleet.push_back(std::make_unique<ElectricBus>("EB-501", 4000, 30, 200, 8));
    for (const auto& v : fleet) {
        std::cout << v->type() << " " << v->getRegistration() << ": ";
        if (v->rent(2))
            std::cout << "rental amount on return = " << v->returnVehicle(3) << '\n';
    }
}

int main() {
    task1Demo();
    task2And3Demo();
    task4Demo();
    task5Demo();
    task6Demo();
    return 0;
}