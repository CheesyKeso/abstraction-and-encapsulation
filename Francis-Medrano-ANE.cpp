#include <iostream>
#include <limits>
using namespace std;

class BankAccount {
protected:
    double balance;

public:
    BankAccount(double initialBalance = 0.0) : balance(initialBalance) {}

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
private:
    const double minimumBalance = 1000.0;

public:
    SavingsAccount() : BankAccount(minimumBalance) {
        
        cout << "Savings Account created with a minimum balance of " << minimumBalance << "." << endl;
    }

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited " << amount << " into Savings Account." << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) override {
        if (amount > 0) {
            if ((balance - amount) >= minimumBalance) {
                balance -= amount;
                cout << "Withdrew " << amount << " from Savings Account." << endl;
            } else {
                cout << "Withdrawal failed! Balance cannot go below the minimum balance of " << minimumBalance << "." << endl;
            }
        } else {
            cout << "Invalid withdrawal amount!" << endl;
        }
    }

    double getBalance() const override {
        return balance;
    }
};

class CurrentAccount : public BankAccount {
public:
    CurrentAccount() : BankAccount(0.0) {
        cout << "Current Account created with an initial balance of 0." << endl;
    }

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited " << amount << " into Current Account." << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) override {
        if (amount > 0) {
            if (balance >= amount) {
                balance -= amount;
                cout << "Withdrew " << amount << " from Current Account." << endl;
            } else {
                cout << "Withdrawal failed! Insufficient balance." << endl;
            }
        } else {
            cout << "Invalid withdrawal amount!" << endl;
        }
    }

    double getBalance() const override {
        return balance;
    }
};

void accountMenu(BankAccount* account) {
    int choice;
    double amount;

    while (true) {
        cout << "\nAccount Menu:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Back\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                account->deposit(amount);
                break;
            case 2:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                account->withdraw(amount);
                break;
            case 3:
                cout << "Balance: " << account->getBalance() << endl;
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void mainMenu() {
    int choice;

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Savings Account\n";
        cout << "2. Current Account\n";
        cout << "3. Exit\n";

        cout << "Choose an option: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                SavingsAccount savings;
                accountMenu(&savings);
                break;
            }
            case 2: {
                CurrentAccount current;
                accountMenu(&current);
                break;
            }
            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
