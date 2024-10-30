#include <iostream>
#include <vector>
#include <iomanip> // for std::fixed and std::setprecision

class Transaction {
public:
    std::string type; // "Deposit" or "Withdrawal"
    double amount;
    std::string date; // For simplicity, we'll keep it as a string

    Transaction(std::string t, double a, std::string d) : type(t), amount(a), date(d) {}
};

class Account {
private:
    double balance;
    std::vector<Transaction> transactions;

public:
    Account() : balance(0.0) {}

    void deposit(double amount, const std::string& date) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, date));
    }

    bool withdraw(double amount, const std::string& date) {
        if (amount > balance) {
            std::cout << "Insufficient funds for withdrawal of " << amount << "\n";
            return false;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount, date));
        return true;
    }

    double getBalance() const {
        return balance;
    }

    void printTransactions() const {
        std::cout << "Transactions:\n";
        for (const auto& transaction : transactions) {
            std::cout << transaction.date << ": " << transaction.type << " of " 
                      << std::fixed << std::setprecision(2) << transaction.amount << "\n";
        }
    }
};

class Customer {
private:
    std::string name;
    Account account;

public:
    Customer(const std::string& n) : name(n) {}

    void deposit(double amount, const std::string& date) {
        account.deposit(amount, date);
        std::cout << "Deposited " << amount << " to " << name << "'s account.\n";
    }

    void withdraw(double amount, const std::string& date) {
        if (account.withdraw(amount, date)) {
            std::cout << "Withdrew " << amount << " from " << name << "'s account.\n";
        }
    }

    void viewAccountInfo() const {
        std::cout << "Account holder: " << name << "\n";
        std::cout << "Balance: " << std::fixed << std::setprecision(2) << account.getBalance() << "\n";
        account.printTransactions();
    }
};

class BankingSystem {
private:
    std::vector<Customer> customers;

public:
    void addCustomer(const std::string& name) {
        customers.push_back(Customer(name));
        std::cout << "Added customer: " << name << "\n";
    }

    Customer* findCustomer(const std::string& name) {
        for (auto& customer : customers) {
            if (customer.name == name) {
                return &customer;
            }
        }
        std::cout << "Customer not found.\n";
        return nullptr;
    }
};

int main() {
    BankingSystem bank;
    int choice;

    do {
        std::cout << "1. Add Customer\n2. Deposit\n3. Withdraw\n4. View Account Info\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cout << "Enter customer name: ";
            std::cin >> name;
            bank.addCustomer(name);
        } else if (choice == 2) {
            std::string name;
            double amount;
            std::string date;
            std::cout << "Enter customer name: ";
            std::cin >> name;
            std::cout << "Enter deposit amount: ";
            std::cin >> amount;
            std::cout << "Enter transaction date: ";
            std::cin >> date;

            Customer* customer = bank.findCustomer(name);
            if (customer) {
                customer->deposit(amount, date);
            }
        } else if (choice == 3) {
            std::string name;
            double amount;
            std::string date;
            std::cout << "Enter customer name: ";
            std::cin >> name;
            std::cout << "Enter withdrawal amount: ";
            std::cin >> amount;
            std::cout << "Enter transaction date: ";
            std::cin >> date;

            Customer* customer = bank.findCustomer(name);
            if (customer) {
                customer->withdraw(amount, date);
            }
        } else if (choice == 4) {
            std::string name;
            std::cout << "Enter customer name: ";
            std::cin >> name;

            Customer* customer = bank.findCustomer(name);
            if (customer) {
                customer->viewAccountInfo();
            }
        }

    } while (choice != 5);

    return 0;
}
