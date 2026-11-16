#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Our own exception class
class ClaimError : public runtime_error {
public:
    ClaimError(string message) : runtime_error(message) {
    }
};

// Check whether the claim can be approved
double approve(double billAmount, double coverAmount) {
    if (billAmount < 0 || coverAmount < 0) {
        throw invalid_argument("Amount cannot be negative");
    }

    if (billAmount > coverAmount) {
        throw ClaimError("Bill is more than the insurance cover");
    }

    return billAmount;
}

// Catch the claim error here, print it and throw it again
double settle(double billAmount, double coverAmount) {
    try {
        return approve(billAmount, coverAmount);
    }
    catch (const ClaimError& e) {
        cout << "Audit: " << e.what() << endl;
        throw;
    }
}

// This class helps us see when an object is destroyed
class Guard {
    string name;

public:
    Guard(string n) {
        name = n;
    }

    ~Guard() {
        cout << "Destroyed: " << name << endl;
    }
};

void validate(double amount) {
    if (amount < 0) {
        throw invalid_argument("Negative amount");
    }

    if (amount > 1000000) {
        throw out_of_range("Amount is too large");
    }

    cout << "Valid ";
}

void process(double amount) {
    try {
        validate(amount);
    }
    catch (const out_of_range& e) {
        cout << "Log: " << e.what() << endl;
        throw;
    }
}

int main() {
    double bills[3] = {40000, 60000, -1};
    double cover = 50000;

    for (int i = 0; i < 3; i++) {
        try {
            double amount = settle(bills[i], cover);
            cout << "Approved: " << amount << endl;
        }
        catch (const ClaimError& e) {
            cout << "Claim rejected: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    cout << "Checking amounts: " << endl;

    double values[3] = {100, -5, 2000000};

    for (int i = 0; i < 3; i++) {
        try {
            process(values[i]);
            cout << "Done" << endl;
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << endl;
        }
    }

    try {
        Guard g("local object");
        throw runtime_error("Example error");
    }
    catch (const exception& e) {
        cout << "Caught in main: " << e.what() << endl;
    }

    return 0;
}
