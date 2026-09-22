#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "../include/transaction.h"

using namespace std;

class BankAccount {
public:
    double deposit(double amount, unordered_map<int, vector<string>> &mp,
                   int account_Number, Transaction_Record &transaction) {
        if (amount <= 0) return 0;
        
        auto it = mp.find(account_Number);

        if (it == mp.end() || it->second.size() < 4) {
            cout << "Invalid account data for account " << account_Number << endl;
            return 0; 
        }

        double balance = 0.0;

        try {
            balance = stod(it->second[2]);
        } catch (const invalid_argument &) {
            cout << "Invalid balance format for account " << account_Number << endl;
            return 0;
        } catch (const out_of_range &) {
            cout << "Balance value is out of range for account " << account_Number << endl;
            return 0;
        }
       

        balance += amount;
        it->second[2] = to_string(balance);
        transaction.addTransaction("Deposit", amount);
        return balance;
    }

    void withDraw(double amount, unordered_map<int, vector<string>> &mp,
                  int account_Number, Transaction_Record &transaction) {
        auto it = mp.find(account_Number);

        if (it == mp.end() || it->second.size() < 4) {
            cout << "Invalid account data for account " << account_Number << endl;
            return;
        }

        double balance = 0.0;
        try {
            balance = stod(it->second[2]);
        } catch (const invalid_argument &) {
            cout << "Invalid balance format for account " << account_Number << endl;
            return;
        } catch (const out_of_range &) {
            cout << "Balance value is out of range for account " << account_Number << endl;
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance" << endl;
        } else if (balance - amount < 500) {
            cout << "After withdrawing this amount the balance will be less than 500 rupees." << endl;
            cout << "According to bank rules, at least 500 rupees should remain in the account." << endl;
        } else {
            balance -= amount;
            it->second[2] = to_string(balance);

            transaction.addTransaction("WithDraw", amount);

            cout << "The withdraw was successful. The current balance is: " << balance << endl;
        }
    }

    void displayAccount(unordered_map<int, vector<string>> &mp, int account_Number) const {
        auto it = mp.find(account_Number);

        if (it == mp.end()) {
            cout << "Account number does not exist" << endl;
            return;
        }

        if (it->second.size() < 3) {
            cout << "Account data is incomplete" << endl;
            return;
        }

        cout << "\n=====Account Details=====" << endl;
        cout << "Name: " << it->second[0] << " " << it->second[1] << endl;
        cout << "Balance: " << it->second[2] << endl;
    }
    
};

bool Login(unordered_map<int,vector<string>> &mp) {
    int account_Number;
    cout << "\nEnter the account number:";
    cin  >> account_Number;

    auto it = mp.find(account_Number);
    if (it == mp.end()) {
        cout << "\nAccount does not exist."<<endl;
        return false;
    } else {
        string StoredPin = it->second[3];
        string enteredPin;

        cout << "\nEnter the PIN for the account:";
        cin >> enteredPin;

        if (enteredPin == StoredPin) {
            return true;
        } else {
            false;
        }

    }
}


int main() {
    unordered_map<int, vector<string>> mp;
    unordered_map<int, Transaction_Record> transactions;

    cout << "\n=====Welcome to Banking Management System=====" << endl;

    BankAccount account;

    int accountNumber;
    string name;
    string surname;
    string balance;
    string pin_number;

    ifstream file("data/account.txt");

    if (!file) {
    cout << "Error: Unable to open account data file." << endl;
    return 1;
}

    while (file >> accountNumber >> name >> surname >> balance >> pin_number) {
        mp[accountNumber] = {name, surname, balance,pin_number};
        transactions.emplace(accountNumber, Transaction_Record(accountNumber));
    }


    file.close();

    int acn;
    string str1;
    double amnt;

    ifstream transaction_file("data/transaction.txt");

    if (!transaction_file) {
        cout << "Error: Unable to open transaction data file." << endl;
        return 1;
    }

    while (transaction_file >> acn >> str1 >> amnt) {
        if (transactions.find(acn) == transactions.end()) {
            cout << "Error: Transaction found for unknown account number " << acn << endl;
            return 1;
        }

        transactions.at(acn).addTransaction(str1, amnt);
    }
    transaction_file.close();

    bool authenticate = Login(mp);

    if (!authenticate) {
        cout << "\nYou're PIN is not matching with the account number PIN" << endl;
        cout << "\nYou cannot perform any activity" << endl;
        return 1;
    }

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
            int pin;

            cout << "\nEnter your name: ";
            cin >> name;

            cout << "\nEnter your surname: ";
            cin >> surname;

            cout << "\nEnter your account number: ";
            cin >> account_number;

            if (account_number <= 0) {
                cout << "Account number should be positive" << endl;
                continue;
            }

            if (mp.find(account_number) != mp.end()) {
                cout << "Account already exists" << endl;
                continue;
            }

            cout << "\nEnter the amount for first deposit. Minimum amount is 500: ";
            cin >> amount;

            cout<<"\nEnter the pin for the account:";
            cin >>pin;

            if (amount < 500) {
                cout << "Minimum amount should be 500" << endl;
            } else {
                mp[account_number] = {name, surname, to_string(amount),to_string(pin)};

                auto result = transactions.emplace(
                    account_number,
                    Transaction_Record(account_number)
                );

                result.first->second.addTransaction("InitialDeposit", amount);

                cout << "Account created successfully" << endl;
            }

            continue;
        }

        if (choice == 6) {
            cout << "Thanks for using Banking Management System" << endl;

            ofstream file("data/account.txt");
            try {
                if (!file) {
                    throw runtime_error("Unable to open account file for writing");
                }

                for (const auto &accountData : mp) {
                    if (accountData.second.size() < 4) {
                        throw out_of_range("Account data is incomplete while writing file");
                    }
                    file << accountData.first << " "
                         << accountData.second[0] << " "
                         << accountData.second[1] << " "
                         << accountData.second[2] << " "
                         << accountData.second[3] <<endl;
                }
            } catch (const exception &e) {
                cout << "Exception while writing account file: " << e.what() << endl;
            }

            file.close();
            
            ofstream transaction_file("data/transaction.txt");
            try {
                if (!transaction_file) {
                    throw runtime_error("Unable to open transaction file for writing");
                }

                for (auto &transactionData : transactions) {
                    transactionData.second.saveTransactions(transaction_file);
                }
            } catch (const exception &e) {
                cout << "Exception while writing transaction file: " << e.what() << endl;
            }

            transaction_file.close();

            break;


        }

        if (choice < 1 || choice > 6) {
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

                double current_balance = 0.0;
                try {
                    current_balance = account.deposit(
                        amount,
                        mp,
                        account_Number,
                        transactions.at(account_Number)
                    );
                } catch (const out_of_range &e) {
                    cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                    continue;
                }

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
                    try {
                        account.withDraw(
                            amount,
                            mp,
                            account_Number,
                            transactions.at(account_Number)
                        );
                    } catch (const out_of_range &e) {
                        cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                    }
                }

                break;
            }

            case 3: {
                account.displayAccount(mp, account_Number);
                break;
            }

            case 5: {
                try {
                    transactions.at(account_Number).displayTransaction();
                } catch (const out_of_range &e) {
                    cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                }
                break;
            }
        }
    }

    return 0;
}