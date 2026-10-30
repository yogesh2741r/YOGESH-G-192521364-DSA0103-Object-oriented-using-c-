#include <iostream>
using namespace std;

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(double weightKg, bool express = false, bool insured = false) {
    double amount = weightKg * 20.0;
    if (express) amount += 50.0;
    if (insured) amount += 25.0;
    return amount;
}

double charge(int weightGrams) {
    return (weightGrams / 1000.0) * 20.0;
}

double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    cout << "charge(2) = " << charge(2) << " [int grams overload]\n";
    cout << "charge(2.0) = " << charge(2.0) << " [double kg overload]\n";
    cout << "charge(2.0f) = " << charge(2.0f) << " [float promoted to double]\n";
    cout << "charge(2500) = " << charge(2500) << " [int grams overload]\n";
    cout << "charge(2.5) = " << charge(2.5) << " [double kg overload]\n";
    cout << "charge(Parcel{2.0, true, false}) = "
         << charge(Parcel{2.0, true, false}) << " [Parcel overload]\n";
    return 0;
}