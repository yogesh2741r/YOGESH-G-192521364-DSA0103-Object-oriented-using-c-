#include <iostream>
#include <vector>
#include <chrono>
#include <variant>
#include <stdexcept>
using namespace std;
using namespace chrono;

// Bill classes for virtual function test
class Bill {
public:
    virtual double total() = 0;
    virtual ~Bill() {
    }
};

class OPBill : public Bill {
    double consultation;
    double tests;

public:
    OPBill(double c, double t) {
        consultation = c;
        tests = t;
    }

    double total() {
        return consultation + tests;
    }
};

class IPBill : public Bill {
    int days;
    double room;
    double surgery;

public:
    IPBill(int d, double r, double s) {
        days = d;
        room = r;
        surgery = s;
    }

    double total() {
        return days * room + surgery;
    }
};

// Structure used for switch statement
struct SwitchBill {
    int type;
    double a;
    double b;
    double c;
};

double switchTotal(SwitchBill bill) {
    if (bill.type == 0) {
        return bill.a + bill.b;
    }
    else {
        return bill.a * bill.b + bill.c;
    }
}

// Structures used for variant
struct VariantOP {
    double consultation;
    double tests;
};

struct VariantIP {
    int days;
    double room;
    double surgery;
};

typedef variant<VariantOP, VariantIP> VariantBill;

double variantTotal(VariantBill bill) {
    if (get_if<VariantOP>(&bill) != NULL) {
        VariantOP op = get<VariantOP>(bill);
        return op.consultation + op.tests;
    }
    else {
        VariantIP ip = get<VariantIP>(bill);
        return ip.days * ip.room + ip.surgery;
    }
}

int main(int argc, char* argv[]) {
    int n = 1000000;

    if (argc > 1) {
        n = stoi(argv[1]);
    }

    vector<OPBill> opBills;
    vector<IPBill> ipBills;
    vector<Bill*> virtualBills;
    vector<SwitchBill> switchBills;
    vector<VariantBill> variantBills;

    opBills.reserve(n / 2 + 1);
    ipBills.reserve(n / 2 + 1);

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            opBills.push_back(OPBill(500, 1200));
            switchBills.push_back({0, 500, 1200, 0});
            variantBills.push_back(VariantOP{500, 1200});
        }
        else {
            ipBills.push_back(IPBill(3, 2500, 40000));
            switchBills.push_back({1, 3, 2500, 40000});
            variantBills.push_back(VariantIP{3, 2500, 40000});
        }
    }

    // Add addresses of objects after vectors are filled
    for (int i = 0; i < opBills.size(); i++) {
        virtualBills.push_back(&opBills[i]);
    }

    for (int i = 0; i < ipBills.size(); i++) {
        virtualBills.push_back(&ipBills[i]);
    }

    double sum = 0;
    auto start = steady_clock::now();

    for (int i = 0; i < virtualBills.size(); i++) {
        sum = sum + virtualBills[i]->total();
    }

    auto finish = steady_clock::now();
    cout << "Virtual time: "
         << duration<double, milli>(finish - start).count()
         << " ms. Total: " << sum << endl;

    sum = 0;
    start = steady_clock::now();

    for (int i = 0; i < switchBills.size(); i++) {
        sum = sum + switchTotal(switchBills[i]);
    }

    finish = steady_clock::now();
    cout << "Switch time: "
         << duration<double, milli>(finish - start).count()
         << " ms. Total: " << sum << endl;

    sum = 0;
    start = steady_clock::now();

    for (int i = 0; i < variantBills.size(); i++) {
        sum = sum + variantTotal(variantBills[i]);
    }

    finish = steady_clock::now();
    cout << "Variant time: "
         << duration<double, milli>(finish - start).count()
         << " ms. Total: " << sum << endl;

    // Compare normal return-code checking and exceptions
    int testCount = 1000000;
    int invalidPercent[3] = {0, 1, 50};

    for (int test = 0; test < 3; test++) {
        vector<double> amounts(testCount, 100);

        int invalidCount = testCount * invalidPercent[test] / 100;

        for (int i = 0; i < invalidCount; i++) {
            amounts[i] = -1;
        }

        int accepted = 0;
        start = steady_clock::now();

        for (int i = 0; i < testCount; i++) {
            if (amounts[i] >= 0) {
                accepted++;
            }
        }

        finish = steady_clock::now();
        cout << "Return code, " << invalidPercent[test]
             << "% invalid: "
             << duration<double, milli>(finish - start).count()
             << " ms. Accepted: " << accepted << endl;

        accepted = 0;
        start = steady_clock::now();

        for (int i = 0; i < testCount; i++) {
            try {
                if (amounts[i] < 0) {
                    throw invalid_argument("Invalid amount");
                }
                accepted++;
            }
            catch (const invalid_argument& e) {
                // Invalid amount is skipped
            }
        }

        finish = steady_clock::now();
        cout << "Exception, " << invalidPercent[test]
             << "% invalid: "
             << duration<double, milli>(finish - start).count()
             << " ms. Accepted: " << accepted << endl;
    }

    return 0;
}
