#include <iostream>
#include <string>
using namespace std;

// Base class: Account
class Account {
protected:
    string id;
    double balance;
    int transactionNo;
    string transactionMemo;

public:
    Account(string id, double balance) {
        this->id = id;
        this->balance = balance;
        transactionNo = 0;
        transactionMemo = "";
    }

    virtual ~Account() {}

    virtual bool withdraw(double amount) {
        if (amount <= 0 || balance < amount) {
            return false;
        }
        balance = balance - amount;
        transactionNo++;
        transactionMemo = "Withdraw";
        return true;
    }

    virtual void deposit(double amount) {
        if (amount <= 0) {
            return;
        }
        balance = balance + amount;
        transactionNo++;
        transactionMemo = "Deposit";
    }

    virtual string toString() const {
        return "ID: " + id + ", Balance: " + to_string(balance);
    }

    int getTransactionNo() const { return transactionNo; }
    string getTransactionMemo() const { return transactionMemo; }
};

// Derived class: Saving Account
class SavingAccount : public Account {
private:
    double interestRate;
    int term;

public:
    SavingAccount(string id, double balance, double interestRate, int term)
        : Account(id, balance) {
        this->interestRate = interestRate;
        this->term = term;
    }

    ~SavingAccount() {}

    bool withdraw(double amount) {
        if (amount <= 0 || balance < amount) {
            return false;
        }
        balance = balance - amount;
        transactionNo++;
        transactionMemo = "Saving Withdraw";
        return true;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            return;
        }
        balance = balance + amount;
        transactionNo++;
        transactionMemo = "Saving Deposit";
    }

    string toString() const {
        return "Saving ID: " + id + ", Balance: " + to_string(balance)
            + ", Rate: " + to_string(interestRate)
            + ", Term: " + to_string(term) + " months";
    }
};

// Derived class: Checking Account
class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(string id, double balance, double overdraftLimit)
        : Account(id, balance) {
        this->overdraftLimit = overdraftLimit;
    }

    ~CheckingAccount() {}

    bool withdraw(double amount) {
        if (amount <= 0) {
            return false;
        }
        if (balance - amount < -overdraftLimit) {
            return false;
        }
        balance = balance - amount;
        transactionNo++;
        transactionMemo = "Checking Withdraw";
        return true;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            return;
        }
        balance = balance + amount;
        transactionNo++;
        transactionMemo = "Checking Deposit";
    }

    string toString() const {
        return "Checking ID: " + id + ", Balance: " + to_string(balance)
            + ", Overdraft: " + to_string(overdraftLimit);
    }
};

// Test program
int main() {
    cout << "===== Saving Account Test =====" << endl;
    SavingAccount saving("S001", 1000, 0.03, 12);
    cout << saving.toString() << endl;

    saving.deposit(500);
    cout << "After deposit 500: " << saving.toString() << endl;
    cout << "Transaction No: " << saving.getTransactionNo()
        << ", Memo: " << saving.getTransactionMemo() << endl;

    if (saving.withdraw(200)) {
        cout << "Withdraw 200: success" << endl;
    }
    else {
        cout << "Withdraw 200: failed" << endl;
    }
    cout << saving.toString() << endl << endl;

    cout << "===== Checking Account Test =====" << endl;
    CheckingAccount checking("C001", 500, 300);
    cout << checking.toString() << endl;

    checking.withdraw(600);
    cout << "After withdraw 600: " << checking.toString() << endl;

    if (checking.withdraw(500)) {
        cout << "Withdraw 500 more: success" << endl;
    }
    else {
        cout << "Withdraw 500 more: failed (over limit)" << endl;
    }
    cout << checking.toString() << endl;

    return 0;
}