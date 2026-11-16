#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Common parent class for all bills
class Bill {
protected:
    string patientName;

public:
    Bill(string name) {
        patientName = name;
    }

    virtual double total() = 0;

    virtual string type() {
        return "Bill";
    }

    void display() {
        cout << type() << " - " << patientName << " : " << total() << endl;
    }

    virtual ~Bill() {
    }
};

class OutPatient : public Bill {
    double consultation;
    double tests;

public:
    OutPatient(string name, double c, double t) : Bill(name) {
        consultation = c;
        tests = t;
    }

    double total() {
        return consultation + tests;
    }

    string type() {
        return "Outpatient";
    }
};

class InPatient : public Bill {
    int days;
    double roomCharge;
    double surgeryCharge;

public:
    InPatient(string name, int d, double room, double surgery) : Bill(name) {
        days = d;
        roomCharge = room;
        surgeryCharge = surgery;
    }

    double total() {
        return days * roomCharge + surgeryCharge;
    }

    string type() {
        return "Inpatient";
    }
};

class DayCare : public Bill {
    double packageAmount;

public:
    DayCare(string name, double amount) : Bill(name) {
        packageAmount = amount;
    }

    double total() {
        return packageAmount;
    }

    string type() {
        return "Day care";
    }
};

class Emergency : public Bill {
    double baseCharge;
    double hourlyCharge;
    int hours;

public:
    Emergency(string name, double base, double rate, int h) : Bill(name) {
        baseCharge = base;
        hourlyCharge = rate;
        hours = h;
    }

    double total() {
        return baseCharge + hourlyCharge * hours;
    }

    string type() {
        return "Emergency";
    }
};

// Common parent class for payment methods
class Payer {
public:
    virtual double amountCovered(Bill& bill) = 0;

    virtual ~Payer() {
    }
};

class SelfPay : public Payer {
public:
    double amountCovered(Bill& bill) {
        return 0;
    }
};

class Insurance : public Payer {
    double limit;
    double patientShare;

public:
    Insurance(double l, double share) {
        limit = l;
        patientShare = share;
    }

    double amountCovered(Bill& bill) {
        double amount = bill.total();

        if (amount > limit) {
            amount = limit;
        }

        return amount * (100 - patientShare) / 100;
    }
};

class GovernmentScheme : public Payer {
    double packageAmount;

public:
    GovernmentScheme(double amount) {
        packageAmount = amount;
    }

    double amountCovered(Bill& bill) {
        double amount = bill.total();

        if (amount > packageAmount) {
            amount = packageAmount;
        }

        return amount;
    }
};

class CorporatePayer : public Payer {
    double percentage;

public:
    CorporatePayer(double p) {
        percentage = p;
    }

    double amountCovered(Bill& bill) {
        return bill.total() * percentage / 100;
    }
};

int main() {
    // Create the bill objects
    OutPatient b1("Ravi", 500, 1200);
    InPatient b2("Meena", 3, 2500, 40000);
    DayCare b3("Arun", 18000);
    Emergency b4("Sara", 2000, 750, 4);

    // Store their addresses in one vector
    vector<Bill*> bills;
    bills.push_back(&b1);
    bills.push_back(&b2);
    bills.push_back(&b3);
    bills.push_back(&b4);

    double grandTotal = 0;

    for (int i = 0; i < bills.size(); i++) {
        bills[i]->display();
        grandTotal = grandTotal + bills[i]->total();
    }

    cout << "Grand total: " << grandTotal << endl;

    Insurance insurance(50000, 20);
    cout << "Insurance covers Meena: "
         << insurance.amountCovered(b2) << endl;

    CorporatePayer company(70);
    cout << "Company covers Ravi: "
         << company.amountCovered(b1) << endl;

    return 0;
}
