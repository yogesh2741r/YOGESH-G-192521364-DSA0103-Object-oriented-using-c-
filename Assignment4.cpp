#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// =====================================================
// TASK 1: STAFF PAYROLL
// =====================================================

class Staff
{
protected:
    string name;
    int id;
    double basic;

public:
    Staff(string n, int i, double b)
    {
        name = n;
        id = i;
        basic = b;
    }

    virtual double pay() = 0;

    void display()
    {
        cout << name << " : " << pay() << endl;
    }

    virtual ~Staff() {}
};

class Professor : public Staff
{
    double research;

public:
    Professor(string n, int i, double b, double r) : Staff(n, i, b)
    {
        research = r;
    }

    double pay()
    {
        return basic + basic * 0.42 + research;
    }
};

class LabAssistant : public Staff
{
public:
    LabAssistant(string n, int i, double b) : Staff(n, i, b)
    {
    }

    double pay()
    {
        return basic + basic * 0.42;
    }
};

class GuestFaculty : public Staff
{
    double hours;
    double rate;

public:
    GuestFaculty(string n, int i, double h, double r) : Staff(n, i, 0)
    {
        hours = h;
        rate = r;
    }

    double pay()
    {
        return hours * rate;
    }
};

void task1()
{
    cout << "\nTASK 1 - STAFF PAYROLL\n";

    Professor p("Anita", 101, 50000, 8000);
    LabAssistant l("Ravi", 102, 30000);
    GuestFaculty g("Meera", 103, 20, 1000);

    Staff* staff[3];

    staff[0] = &p;
    staff[1] = &l;
    staff[2] = &g;

    for (int i = 0; i < 3; i++)
    {
        staff[i]->display();
    }
}

// =====================================================
// TASK 2 AND TASK 3: INHERITANCE AND CONSTRUCTORS
// =====================================================

class Address
{
    string city;
    int pin;

public:
    Address(string c, int p)
    {
        city = c;
        pin = p;
    }

    string getAddress()
    {
        return city + "-" + to_string(pin);
    }
};

class Course
{
    string courseName;

public:
    Course(string c)
    {
        courseName = c;
    }

    string getCourse()
    {
        return courseName;
    }
};

class Person
{
protected:
    string name;
    int id;
    string phone;
    Address address;

public:
    Person(string n, int i, string ph, Address a) : address(a)
    {
        name = n;
        id = i;
        phone = ph;
        cout << "Person constructor\n";
    }

    virtual ~Person()
    {
        cout << "Person destructor\n";
    }
};

class Student : virtual public Person
{
protected:
    string programme;
    double cgpa;
    Course course;

public:
    Student(string n, int i, string ph, Address a,
            string prog, double g, Course c)
        : Person(n, i, ph, a), course(c)
    {
        programme = prog;
        cgpa = g;
        cout << "Student constructor\n";
    }

    ~Student()
    {
        cout << "Student destructor\n";
    }
};

class StaffMember : virtual public Person
{
protected:
    string department;
    double salary;

public:
    StaffMember(string n, int i, string ph, Address a,
                string dept, double s)
        : Person(n, i, ph, a)
    {
        department = dept;
        salary = s;
        cout << "Staff constructor\n";
    }

    ~StaffMember()
    {
        cout << "Staff destructor\n";
    }
};

class TeachingAssistant : public Student, public StaffMember
{
public:
    TeachingAssistant(string n, int i, string ph, Address a,
                      string prog, double g, Course c,
                      string dept, double s)
        : Person(n, i, ph, a),
          Student(n, i, ph, a, prog, g, c),
          StaffMember(n, i, ph, a, dept, s)
    {
        cout << "TeachingAssistant constructor\n";
    }

    ~TeachingAssistant()
    {
        cout << "TeachingAssistant destructor\n";
    }
};

class ResearchScholar : public Student
{
    double fellowship;

public:
    ResearchScholar(string n, int i, string ph, Address a,
                    string prog, double g, Course c, double f)
        : Person(n, i, ph, a), Student(n, i, ph, a, prog, g, c)
    {
        fellowship = f;
    }
};

void task2And3()
{
    cout << "\nTASK 2 AND TASK 3 - CONSTRUCTORS\n";

    Address a("Salem", 636001);
    Course c("C++");

    cout << "\nCreating Student object\n";
    Student s("Kavya", 201, "9876543210", a, "CSE", 8.5, c);

    cout << "\nCreating Staff object\n";
    StaffMember st("Arun", 202, "9876543211", a, "IT", 40000);

    cout << "\nCreating TeachingAssistant object\n";
    TeachingAssistant ta("Ravi", 203, "9876543212", a,
                         "CSE", 8.7, c, "IT", 30000);

    cout << "\nSize of TeachingAssistant: " << sizeof(ta) << endl;
}

// =====================================================
// TASK 4: POINTERS TO DERIVED CLASSES
// =====================================================

class Account
{
public:
    double rate()
    {
        return 3.5;
    }

    virtual double vrate()
    {
        return 3.5;
    }

    virtual ~Account()
    {
        cout << "Account destructor\n";
    }
};

class SeniorAccount : public Account
{
    double* history;

public:
    SeniorAccount()
    {
        history = new double[100];
    }

    double rate()
    {
        return 4.0;
    }

    double vrate()
    {
        return 4.0;
    }

    ~SeniorAccount()
    {
        delete[] history;
        cout << "SeniorAccount destructor\n";
    }
};

void task4()
{
    cout << "\nTASK 4 - ACCOUNT POINTERS\n";

    Account* accounts[2];

    accounts[0] = new Account();
    accounts[1] = new SeniorAccount();

    for (int i = 0; i < 2; i++)
    {
        cout << "Normal rate: " << accounts[i]->rate() << endl;
        cout << "Virtual rate: " << accounts[i]->vrate() << endl;
    }

    for (int i = 0; i < 2; i++)
    {
        delete accounts[i];
    }

    SeniorAccount senior;
    Account copy = senior;

    Account* p = &senior;

    cout << "Output prediction example: ";
    cout << p->rate() << " " << p->vrate() << " " << copy.vrate() << endl;
}

// =====================================================
// TASK 5: POINTERS TO OBJECTS AND this POINTER
// =====================================================

class Cart
{
    string items[10];
    double prices[10];
    int n;
    double discount;

public:
    Cart()
    {
        n = 0;
        discount = 0;
    }

    Cart& add(string item, double price)
    {
        if (n < 10)
        {
            items[n] = item;
            prices[n] = price;
            n++;
        }

        return *this;
    }

    Cart& setDiscount(double discount)
    {
        this->discount = discount;
        return *this;
    }

    double total()
    {
        double sum = 0;

        for (int i = 0; i < n; i++)
        {
            sum = sum + prices[i];
        }

        return sum * (100 - discount) / 100;
    }
};

void task5()
{
    cout << "\nTASK 5 - CART OBJECTS\n";

    // 1. Accessing an object directly
    Cart c1;
    c1.add("Rice", 60);

    // 2. Accessing an object using a pointer
    Cart* ptr = &c1;
    ptr->add("Dal", 120);

    // 3. Accessing an object using a reference
    Cart& ref = c1;
    ref.add("Oil", 180);

    // 4. Creating an object using new
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Milk", 40);

    cout << "Cart total: " << c1.total() << endl;
    cout << "Dynamic cart total: " << dynamicCart->total() << endl;

    delete dynamicCart;

    // Method chaining
    Cart c2;
    c2.add("Rice", 60).add("Dal", 120).setDiscount(10);
    cout << fixed << setprecision(2);
    cout << "Chained cart total: " << c2.total() << endl;

    // Array of pointers to Cart objects
    Cart c3;
    c3.add("Book", 200);

    Cart* carts[3];
    carts[0] = &c1;
    carts[1] = &c2;
    carts[2] = &c3;

    int highest = 0;

    for (int i = 1; i < 3; i++)
    {
        if (carts[i]->total() > carts[highest]->total())
        {
            highest = i;
        }
    }

    cout << "Highest cart total: " << carts[highest]->total() << endl;
}

// =====================================================
// TASK 6: VEHICLE RENTAL
// =====================================================

class Vehicle
{
protected:
    string registration;
    double dailyRate;
    bool rented;
    int rentedDays;

public:
    Vehicle(string r, double rate)
    {
        registration = r;
        dailyRate = rate;
        rented = false;
        rentedDays = 0;
    }

    virtual double charge(int days) = 0;

    bool rent(int days)
    {
        if (rented == true || days <= 0)
        {
            return false;
        }

        rented = true;
        rentedDays = days;
        return true;
    }

    double returnVehicle(int actualDays)
    {
        if (rented == false)
        {
            return 0;
        }

        int lateDays = actualDays - rentedDays;

        if (lateDays < 0)
        {
            lateDays = 0;
        }

        double amount = charge(rentedDays);
        amount = amount + lateDays * dailyRate * 1.25;

        rented = false;
        rentedDays = 0;

        return amount;
    }

    string getRegistration()
    {
        return registration;
    }

    virtual string getType() = 0;

    virtual ~Vehicle() {}
};

class Bicycle : public Vehicle
{
public:
    Bicycle(string r, double rate) : Vehicle(r, rate)
    {
    }

    double charge(int days)
    {
        return dailyRate * days;
    }

    string getType()
    {
        return "Bicycle";
    }
};

class MotorVehicle : public Vehicle
{
protected:
    double fuelOrChargeLevel;
    string serviceDueDate;

public:
    MotorVehicle(string r, double rate, double level, string due)
        : Vehicle(r, rate)
    {
        fuelOrChargeLevel = level;
        serviceDueDate = due;
    }
};

class TwoWheeler : public MotorVehicle
{
public:
    TwoWheeler(string r, double rate, double fuel, string due)
        : MotorVehicle(r, rate, fuel, due)
    {
    }

    double charge(int days)
    {
        return dailyRate * days;
    }

    string getType()
    {
        return "TwoWheeler";
    }
};

class Car : public MotorVehicle
{
protected:
    int seatingCapacity;

public:
    Car(string r, double rate, double fuel, string due, int seats)
        : MotorVehicle(r, rate, fuel, due)
    {
        seatingCapacity = seats;
    }

    double charge(int days)
    {
        return dailyRate * days;
    }

    string getType()
    {
        return "Car";
    }
};

class ElectricCar : public Car
{
    double batteryCapacity;
    double kWhRate;

public:
    ElectricCar(string r, double rate, double fuel, string due,
                int seats, double battery, double unitRate)
        : Car(r, rate, fuel, due, seats)
    {
        batteryCapacity = battery;
        kWhRate = unitRate;
    }

    double charge(int days)
    {
        return dailyRate * days + batteryCapacity * kWhRate;
    }

    string getType()
    {
        return "ElectricCar";
    }
};

// New type added without changing the existing vehicle classes
class ElectricBus : public Vehicle
{
    int seatingCapacity;
    double batteryCapacity;
    double kWhRate;

public:
    ElectricBus(string r, double rate, int seats, double battery, double unitRate)
        : Vehicle(r, rate)
    {
        seatingCapacity = seats;
        batteryCapacity = battery;
        kWhRate = unitRate;
    }

    double charge(int days)
    {
        return dailyRate * days + batteryCapacity * kWhRate;
    }

    string getType()
    {
        return "ElectricBus";
    }
};

void task6()
{
    cout << "\nTASK 6 - VEHICLE RENTAL\n";

    Bicycle bicycle("BIC101", 100);
    TwoWheeler bike("BIKE201", 250, 80, "2027-01-01");
    Car car("CAR301", 1500, 70, "2027-02-01", 5);
    ElectricCar electricCar("EV401", 1800, 90, "2027-03-01", 5, 60, 8);
    ElectricBus electricBus("BUS501", 4000, 30, 200, 8);

    Vehicle* fleet[5];

    fleet[0] = &bicycle;
    fleet[1] = &bike;
    fleet[2] = &car;
    fleet[3] = &electricCar;
    fleet[4] = &electricBus;

    for (int i = 0; i < 5; i++)
    {
        cout << fleet[i]->getType() << " : ";

        if (fleet[i]->rent(2))
        {
            double amount = fleet[i]->returnVehicle(3);
            cout << "Rental amount = " << amount << endl;
        }
    }
}

int main()
{
    task1();

    task2And3();

    task4();

    task5();

    task6();

    return 0;
}
