#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "../include/transaction.h"

using namespace std;

class BankAccount {
public:
    double deposit(double amount, unordered_map<int, vector<string>> &mp,
                   int account_Number, Transaction_Record &transaction) {
        if (amount <= 0) return 0;

        double balance = stod(mp[account_Number][2]);
        balance += amount;

        mp[account_Number][2] = to_string(balance);

        transaction.addTransaction("Deposit +" + to_string(amount));

        return balance;
    }

    void withDraw(double amount, unordered_map<int, vector<string>> &mp,
                  int account_Number, Transaction_Record &transaction) {
        double balance = stod(mp[account_Number][2]);

        if (amount > balance) {
            cout << "Insufficient balance" << endl;
        } else if (balance - amount < 500) {
            cout << "After withdrawing this amount the balance will be less than 500 rupees." << endl;
            cout << "According to bank rules, at least 500 rupees should remain in the account." << endl;
        } else {
            balance -= amount;
            mp[account_Number][2] = to_string(balance);

            transaction.addTransaction("WithDraw -" + to_string(amount));

            cout << "The withdraw was successful. The current balance is: " << balance << endl;
        }
    }

    void displayAccount(unordered_map<int, vector<string>> &mp, int account_Number) const {
        cout << "\n=====Account Details=====" << endl;
        cout << "Name: " << mp[account_Number][0] << " " << mp[account_Number][1] << endl;
        cout << "Account Number: " << account_Number << endl;
        cout << "Balance: " << mp[account_Number][2] << endl;
    }
};

int main() {
    unordered_map<int, vector<string>> mp;
    unordered_map<int, Transaction_Record> transactions;

    cout << "\n=====Welcome to Banking Management System=====" << endl;

    BankAccount account;

    ifstream file("data/account.txt");

    int accountNumber;
    string name;
    string surname;
    string balance;

    while (file >> accountNumber >> name >> surname >> balance) {
        mp[accountNumber] = {name, surname, balance};
        transactions.emplace(accountNumber, Transaction_Record(accountNumber));
    }

    file.close();

    while (true) {
        cout << "\n=====Main Menu=====" << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. WithDraw Money" << endl;
        cout << "3. Check Account" << endl;
        cout << "4. Create Account" << endl;
        cout << "5. Transaction History" << endl;
        cout << "6. Exit" << endl;

        int choice;
        int account_Number;

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 4) {
            string name;
            string surname;
            int account_number;
            double amount;

            cout << "\nEnter your name: ";
            cin >> name;

            cout << "\nEnter your surname: ";
            cin >> surname;

            cout << "\nEnter your account number: ";
            cin >> account_number;

            if (mp.find(account_number) != mp.end()) {
                cout << "Account already exists" << endl;
                continue;
            }

            cout << "\nEnter the amount for first deposit. Minimum amount is 500: ";
            cin >> amount;

            if (amount < 500) {
                cout << "Minimum amount should be 500" << endl;
            } else {
                mp[account_number] = {name, surname, to_string(amount)};

                auto result = transactions.emplace(
                    account_number,
                    Transaction_Record(account_number)
                );

                result.first->second.addTransaction("Initial Deposit: +" + to_string(amount));

                cout << "Account created successfully" << endl;
            }

            continue;
        }

        if (choice == 6) {
            cout << "Thanks for using Banking Management System" << endl;

            ofstream file("data/account.txt");

            for (auto accountData : mp) {
                file << accountData.first << " "
                     << accountData.second[0] << " "
                     << accountData.second[1] << " "
                     << accountData.second[2] << endl;
            }

            file.close();
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid Choice" << endl;
            continue;
        }

        cout << "\nEnter your account number: ";
        cin >> account_Number;

        if (mp.find(account_Number) == mp.end()) {
            cout << "\nYou don't have account here. First make the account." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                double amount;

                cout << "\nEnter the amount: ";
                cin >> amount;

                double current_balance = account.deposit(
                    amount,
                    mp,
                    account_Number,
                    transactions.at(account_Number)
                );

                if (current_balance) {
                    cout << "The amount is deposited successfully. The current balance is: "
                         << current_balance << endl;
                } else {
                    cout << "Amount should be greater than 0. Deposit unsuccessful." << endl;
                }

                break;
            }

            case 2: {
                double amount;

                cout << "\nEnter the amount to withDraw: ";
                cin >> amount;

                if (amount <= 0) {
                    cout << "The amount should be greater than 0" << endl;
                } else {
                    account.withDraw(
                        amount,
                        mp,
                        account_Number,
                        transactions.at(account_Number)
                    );
                }

                break;
            }

            case 3: {
                account.displayAccount(mp, account_Number);
                break;
            }

            case 5: {
                transactions.at(account_Number).displayTransaction();
                break;
            }
        }
    }

    return 0;
}