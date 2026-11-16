#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

class Bill {
public:
    virtual double total() = 0;
    virtual string type() = 0;

    virtual ~Bill() {
    }
};

class OutPatient : public Bill {
    double consultation;
    double tests;

public:
    OutPatient(double c, double t) {
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
    double room;
    double procedure;

public:
    InPatient(int d, double r, double p) {
        days = d;
        room = r;
        procedure = p;
    }

    double total() {
        return days * room + procedure;
    }

    string type() {
        return "Inpatient";
    }
};

// New bill type. The old classes do not need to be changed.
class Telemedicine : public Bill {
    double consultation;
    double platformFee;

public:
    Telemedicine(double c, double fee) {
        consultation = c;
        platformFee = fee;
    }

    double total() {
        return consultation + platformFee;
    }

    string type() {
        return "Telemedicine";
    }
};

class Payer {
public:
    virtual double amountCovered(Bill& bill) = 0;

    virtual ~Payer() {
    }
};

class CorporatePayer : public Payer {
    double percent;

public:
    CorporatePayer(double p) {
        if (p < 0 || p > 100) {
            throw invalid_argument("Percentage should be between 0 and 100");
        }
        percent = p;
    }

    double amountCovered(Bill& bill) {
        return bill.total() * percent / 100;
    }
};

int main() {
    OutPatient b1(500, 1200);
    InPatient b2(3, 2500, 40000);
    Telemedicine b3(800, 100);

    vector<Bill*> bills;
    bills.push_back(&b1);
    bills.push_back(&b2);
    bills.push_back(&b3);

    for (int i = 0; i < bills.size(); i++) {
        cout << bills[i]->type() << " bill: "
             << bills[i]->total() << endl;
    }

    CorporatePayer company(70);

    cout << "Company covers telemedicine bill: "
         << company.amountCovered(b3) << endl;

    return 0;
}
