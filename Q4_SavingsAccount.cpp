#include <iostream>
using namespace std;

class SavingsAccount {
private:
    long long accountNumber;
    double balance;
    double transactions[10];
    int count;

    void addTransaction(double amount) {
        if (count < 10) {
            transactions[count++] = amount;
        } else {
            for (int i = 1; i < 10; ++i) {
                transactions[i - 1] = transactions[i];
            }
            transactions[9] = amount;
        }
    }

public:
    SavingsAccount(long long no, double opening)
        : accountNumber(no), balance(opening), count(0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            addTransaction(amount);
        }
    }

    bool withdraw(double amount);
    void miniStatement() const;

    double getBalance() const {
        return balance;
    }
};

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }
    balance -= amount;
    addTransaction(-amount);
    return true;
}

void SavingsAccount::miniStatement() const {
    cout << "Mini statement for account " << accountNumber << ":\n";
    for (int i = 0; i < count; ++i) {
        cout << transactions[i] << '\n';
    }
}

int main() {
    SavingsAccount account(192521364, 5000);

    account.deposit(1000);
    account.withdraw(500);
    account.deposit(250);
    account.withdraw(100);

    cout << "Balance: " << account.getBalance() << '\n';
    account.miniStatement();

    return 0;
}