#include <iostream>
#include<sodium.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "../include/transaction.h"


class BankAccount {
public:
    double deposit(double amount, std::unordered_map<int, std::vector<std::string>> &mp,
                   int account_Number, Transaction_Record &transaction) {
        if (amount <= 0) return 0;
        
        auto it = mp.find(account_Number);

        if (it == mp.end() || it->second.size() < 5) {
            std::cout << "Invalid account data for account " << account_Number << endl;
            return 0; 
        }

        double balance = 0.0;

        try {
            balance = stod(it->second[2]);
        } catch (const invalid_argument &) {
            std::cout << "Invalid balance format for account " << account_Number << endl;
            return 0;
        } catch (const out_of_range &) {
            std::cout << "Balance value is out of range for account " << account_Number << endl;
            return 0;
        }
       

        balance += amount;
        it->second[2] = to_string(balance);
        transaction.addTransaction("Deposit", amount);
        return balance;
    }

    void withDraw(double amount, std::unordered_map<int, std::vector<std::string>> &mp,
                  int account_Number, Transaction_Record &transaction) {
        auto it = mp.find(account_Number);

        if (it == mp.end() || it->second.size() < 5) {
            std::cout << "Invalid account data for account " << account_Number << endl;
            return;
        }

        double balance = 0.0;
        try {
            balance = stod(it->second[2]);
        } catch (const invalid_argument &) {
            std::cout << "Invalid balance format for account " << account_Number << endl;
            return;
        } catch (const out_of_range &) {
            std::cout << "Balance value is out of range for account " << account_Number << endl;
            return;
        }

        if (amount > balance) {
            std::cout << "Insufficient balance" << endl;
        } else if (balance - amount < 500) {
            std::cout << "After withdrawing this amount the balance will be less than 500 rupees." << endl;
            std::cout << "According to bank rules, at least 500 rupees should remain in the account." << endl;
        } else {
            balance -= amount;
            it->second[2] = to_string(balance);

            transaction.addTransaction("WithDraw", amount);

            std::cout << "The withdraw was successful. The current balance is: " << balance << endl;
        }
    }

    void displayAccount(std::unordered_map<int, std::vector<std::string>> &mp, int account_Number) const {
        auto it = mp.find(account_Number);

        if (it == mp.end()) {
            std::cout << "Account number does not exist" << endl;
            return;
        }

        if (it->second.size() < 5) {
            std::cout << "Account data is incomplete" << endl;
            return;
        }

        std::cout << "\n=====Account Details=====" << endl;
        std::cout << "Name: " << it->second[0] << " " << it->second[1] << endl;
        std::cout << "Balance: " << it->second[2] << endl;
    }
    
};

bool Login(std::unordered_map<int,std::vector<std::string>> &mp) {
    string enteredpin;
    int account_number;

    std::cout << "\nEnter the account number:";
    std::cin >> account_number;

    auto it = mp.find(account_number);

    
    
    if (it == mp.end()) {
        std::cout << "\nAccount Number does not exist." << endl;
        return false;
    }else if(it->second.size() < 5) {
        std::cout << "\nAccount data is incomplete." << endl;
        return false;
        
    } else if (it->second[4]=="Inactive") {
        std::cout <<"\n Account is locked.Access denied please contact the bank";
        return false;
    }else {
        std::cout << "\nYou have only 3 attempts to login"<< endl;
        const string &storedhash =  it->second[3];
        int attempts = 0;
        int remianing = 3;
        while (attempts < 3) {
            std::cout << "\nEnter the pin number:";
            std::cin >> enteredpin;

            if (crypto_pwhash_str_verify(storedhash.c_str(), enteredpin.c_str(), enteredpin.length()) == 0) {
                return true;
            }
            remianing--;
            std::cout << "\nRemaining attempts:"<<remianing;
            attempts++;

        }

    }
    
    std::cout << "\nYou have exhausted your attempts.";
    std::cout << "\nLogin Failed";
    it->second[4] = "Inactive";
    return false;


}


int main() {
    std::unordered_map<int, std::vector<std::string>> mp;
    std::unordered_map<int, Transaction_Record> transactions;
    if (sodium_init() == -1){
    std::cout << "Security initialization failed." << std::endl;
    return 1;
    }

    std::cout << "\n=====Welcome to Banking Management System=====" << endl;

    BankAccount account;

    int accountNumber;
    string name;
    string surname;
    string balance;
    string pin_number;
    string account_status;

    ifstream file("data/account.txt");

    if (!file) {
    std::cout << "Error: Unable to open account data file." << endl;
    return 1;
}

    while (file >> accountNumber >> name >> surname >> balance >> pin_number >> account_status) {
        mp[accountNumber] = {name, surname, balance,pin_number, account_status};
        transactions.emplace(accountNumber, Transaction_Record(accountNumber));
    }


    file.close();

    int acn;
    string str1;
    double amnt;

    ifstream transaction_file("data/transaction.txt");

    if (!transaction_file) {
        std::cout << "Error: Unable to open transaction data file." << endl;
        return 1;
    }

    while (transaction_file >> acn >> str1 >> amnt) {
        if (transactions.find(acn) == transactions.end()) {
            std::cout << "Error: Transaction found for unknown account number " << acn << endl;
            return 1;
        }

        transactions.at(acn).addTransaction(str1, amnt);
    }
    transaction_file.close();

    char hasAccount;
    std::cout<< "\n Do you have an account? (y/n): ";
    std::cin>> hasAccount;

    if (hasAccount == 'y' || hasAccount == 'Y') {
        if (!Login(mp)) {
            std::cout << "\nInvalid account number or pin. Exiting." << endl;
            ofstream file("data/account.txt");
            try {
                if (!file) {
                    throw runtime_error("Unable to open account file for writing");
                }

                for (const auto &accountData : mp) {
                    if (accountData.second.size() < 5) {
                        throw out_of_range("Account data is incomplete while writing file");
                    }
                    file << accountData.first << " "
                         << accountData.second[0] << " "
                         << accountData.second[1] << " "
                         << accountData.second[2] << " "
                         << accountData.second[3] << " "
                         << accountData.second[4] << endl;
                }
            } catch (const exception &e) {
                std::cout << "Exception while writing account file: " << e.what() << endl;
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
                std::cout << "Exception while writing transaction file: " << e.what() << endl;
            }

            transaction_file.close();
            return 1;
        }
    } else if (hasAccount == 'n' || hasAccount == 'N') {
        std::cout << "\nPlease create an account first." << endl;
    } else {
        std::cout << "\nInvalid input. Exiting." << endl;
        return 1;
    }

    while (true) {
        std::cout << "\n=====Main Menu=====" << endl;
        std::cout << "1. Deposit Money" << endl;
        std::cout << "2. WithDraw Money" << endl;
        std::cout << "3. Check Account" << endl;
        std::cout << "4. Create Account" << endl;
        std::cout << "5. Transaction History" << endl;
        std::cout << "6. Exit" << endl;

        int choice;
        int account_Number;

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 4) {
            string name;
            string surname;
            int account_number;
            double amount;
            string pin;
            string account_status;

            std::cout << "\nEnter your name: ";
            std::cin >> name;

            std::cout << "\nEnter your surname: ";
            std::cin >> surname;

            std::cout << "\nEnter your account number: ";
            std::cin >> account_number;

            if (account_number <= 0) {
                std::cout << "Account number should be positive" << endl;
                continue;
            }

            if (mp.find(account_number) != mp.end()) {
                std::cout << "Account already exists" << endl;
                continue;
            }

            std::cout << "\nEnter the amount for first deposit. Minimum amount is 500: ";
            std::cin >> amount;

            std::cout<<"\nEnter the pin for the account:";
            std::cin >> pin;

            size_t pin_length = pin.length();
            char hashed_pin[crypto_pwhash_STRBYTES]; 

            if (crypto_pwhash_str(
                hashed_pin,
                pin.c_str(),
                pin_length,
                crypto_pwhash_OPSLIMIT_INTERACTIVE,
                crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
                std::cout<<"\nPIN hashing failed" << endl;
                continue;
            }
            string storedHash = hashed_pin;
            

            if (amount < 500) {
                std::cout << "Minimum amount should be 500" << endl;
            } else {
                mp[account_number] = {name, surname, to_string(amount),storedHash, "Active"};

                auto result = transactions.emplace(
                    account_number,
                    Transaction_Record(account_number)
                );

                result.first->second.addTransaction("InitialDeposit", amount);

                std::cout << "Account created successfully" << endl;
            }

            continue;
        }

        if (choice == 6) {
            std::cout << "Thanks for using Banking Management System" << endl;

            std::ofstream file("data/account.txt");
            try {
                if (!file) {
                    throw std::runtime_error("Unable to open account file for writing");
                }

                for (const auto &accountData : mp) {
                    if (accountData.second.size() < 5) {
                        throw std::out_of_range("Account data is incomplete while writing file");
                    }
                    file << accountData.first << " "
                         << accountData.second[0] << " "
                         << accountData.second[1] << " "
                         << accountData.second[2] << " "
                         << accountData.second[3] << " "
                         << accountData.second[4] << endl;
                }
            } catch (const exception &e) {
                std::cout << "Exception while writing account file: " << e.what() << endl;
            }

            file.close();
            
            std::ofstream transaction_file("data/transaction.txt");
            try {
                if (!transaction_file) {
                    throw std::runtime_error("Unable to open transaction file for writing");
                }

                for (auto &transactionData : transactions) {
                    transactionData.second.saveTransactions(transaction_file);
                }
            } catch (const exception &e) {
                std::cout << "Exception while writing transaction file: " << e.what() << endl;
            }

            transaction_file.close();

            break;


        }

        if (choice < 1 || choice > 6) {
            std::cout << "Invalid Choice" << endl;
            continue;
        }

        std::cout << "\nEnter your account number: ";
        std::cin >> account_Number;

        if (mp.find(account_Number) == mp.end()) {
            std::cout << "\nYou don't have account here. First make the account." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                double amount;

                std::cout << "\nEnter the amount: ";
                std::cin >> amount;

                double current_balance = 0.0;
                try {
                    current_balance = account.deposit(
                        amount,
                        mp,
                        account_Number,
                        transactions.at(account_Number)
                    );
                } catch (const out_of_range &e) {
                    std::cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                    continue;
                }

                if (current_balance) {
                    std::cout << "The amount is deposited successfully. The current balance is: "
                         << current_balance << endl;
                } else {
                    std::cout << "Amount should be greater than 0. Deposit unsuccessful." << endl;
                }

                break;
            }

            case 2: {
                double amount;

                std::cout << "\nEnter the amount to withDraw: ";
                std::cin >> amount;

                if (amount <= 0) {
                    std::cout << "The amount should be greater than 0" << endl;
                } else {
                    try {
                        account.withDraw(
                            amount,
                            mp,
                            account_Number,
                            transactions.at(account_Number)
                        );
                    } catch (const out_of_range &e) {
                        std::cout << "Exception: Account not found in transaction records - " << e.what() << endl;
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
                    std::cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                }
                break;
            }
        }
    }

    return 0;
}