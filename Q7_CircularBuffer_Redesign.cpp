#include <iostream>
using namespace std;

class CircularHistory {
private:
    static const int CAPACITY = 10;
    double history[CAPACITY];
    int count;
    int start; // Index of the oldest stored transaction.

public:
    CircularHistory() : count(0), start(0) {}

    void add(double amount) {
        if (count < CAPACITY) {
            history[(start + count) % CAPACITY] = amount;
            ++count;
        } else {
            history[start] = amount;
            start = (start + 1) % CAPACITY;
        }
    }

    void print() const {
        for (int i = 0; i < count; ++i) {
            cout << history[(start + i) % CAPACITY] << '\n';
        }
    }
};

int main() {
    CircularHistory transactions;

    for (int value = 1; value <= 12; ++value) {
        transactions.add(value);
    }

    cout << "Latest 10 transactions:\n";
    transactions.print();

    return 0;
}