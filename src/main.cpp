#include <iostream>
#include<sodium.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "../include/transaction.h"
#include "../include/pin_strength.h"


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

bool activate(std::unordered_map<int, std::vector<std::string>>::iterator &it) {

    const string &storedpin = it->second[3];

    int attempts = 0;
    int remaining = 3;
    string enteredpin;
    while (attempts < 3) {
        std::cout << "\nEnter the pin number:";
        std::cin >> enteredpin;
        if (crypto_pwhash_str_verify(storedpin.c_str(), enteredpin.c_str(), enteredpin.length()) == 0) {
            cout << "\nAccount is activated successfully.";
            it->second[4] = "Active";
            return true;
        } else {
            cout << "\nEntered wrong pin";
            remaining--;
            if (remaining!= 0)std::cout << "\nRemaining attempts:"<<remaining;
            attempts++;
        }
    }

    return false;
}

void LoadAccounts(std::unordered_map<int, std::vector<std::string>> &mp,
                  std::unordered_map<int, Transaction_Record> &transactions) {
    ifstream file("data/account.txt");

    if (!file) {
        std::cout << "Error: Unable to open account data file." << endl;
        return;
    }

    int accountNumber;
    string name;
    string surname;
    string balance;
    string pin_number;
    string account_status;

    while (file >> accountNumber >> name >> surname >> balance >> pin_number >> account_status) {
        mp[accountNumber] = {name, surname, balance, pin_number, account_status};
        transactions.emplace(accountNumber, Transaction_Record(accountNumber));
    }
}

void LoadTransactions(std::unordered_map<int, Transaction_Record> &transactions) {
    ifstream transaction_file("data/transaction.txt");

    if (!transaction_file) {
        std::cout << "Error: Unable to open transaction data file." << endl;
        return;
    }

    int acn;
    string str1;
    double amnt;

    while (transaction_file >> acn >> str1 >> amnt) {
        if (transactions.find(acn) == transactions.end()) {
            std::cout << "Error: Transaction found for unknown account number " << acn << endl;
            continue; 
        }

        transactions.at(acn).addTransaction(str1, amnt);
    }

}

void SaveAccounts(const std::unordered_map<int, std::vector<std::string>> &mp) {
    ofstream file("data/account.txt");

    if (!file) {
        std::cout << "Error: Unable to open account data file for writing." << endl;
        return;
    }

    for (const auto &accountData : mp) {
        if (accountData.second.size() < 5) {
            std::cout << "Error: Incomplete account data for account number " << accountData.first << endl;
            continue; 
        }
        file << accountData.first << " "
             << accountData.second[0] << " "
             << accountData.second[1] << " "
             << accountData.second[2] << " "
             << accountData.second[3] << " "
             << accountData.second[4] << endl;
    }

}

void Savetransactions(const std::unordered_map<int, Transaction_Record> &transactions) {
    std::ofstream transaction_file("data/transaction.txt");

    if (!transaction_file) {
        std::cout << "Error: Unable to open transaction data file for writing." << endl;
        return;
    }

    for (const auto &transactionData : transactions) {
        transactionData.second.saveTransactions(transaction_file);
    }
}

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
        std::cout <<"\n Account is locked.";
        char choice;
        std::cout <<"\nDo you want to activate it(Enter y for Yes and n for No):";
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            return activate(it);
        } else if (choice == 'N' || choice == 'n') {
            return false;
        } else {
            std::cout <<"\nInvalid choice";
            return false;
        }
    }else {
        std::cout << "\nYou have only 3 attempts to login if didn't able ton login your account will be locked."<< endl;
        const string &storedhash =  it->second[3];
        int attempts = 0;
        int remaining = 3;
        while (attempts < 3) {
            std::cout << "\nEnter the pin number:";
            std::cin >> enteredpin;

            if (crypto_pwhash_str_verify(storedhash.c_str(), enteredpin.c_str(), enteredpin.length()) == 0) {
                return true;
            }
            remaining--;
            if ( remaining!= 0)std::cout << "\nRemaining attempts:"<<remaining;
            attempts++;
        }
    }
    
    std::cout << "\nYou have exhausted your attempts.";
    std::cout << "\nLogin Failed";
    it->second[4] = "Inactive";
    return false;


}

std::string GivePIN() {
    std::string Pin_number;
    PINStrength pinChecker;

    while (true) {
        cout << "\nEnter the pin number(atmost there should be 8 digits):";
        cin >> Pin_number;

        if (Pin_number.length() > 8) {
            cout << "\nThere should be atmost 8 digits";
            continue;
        }else if(Pin_number.length() <= 8) {
            bool valid = true;
            for (char ch : Pin_number) {
                if (ch < '0' || ch > '9') {
                    cout << "\nYour input pin number is invalid because it contains letters,and symbols";
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
        }
        bool isWeak = pinChecker.isWeak(Pin_number);

        if (isWeak) {
            cout << "\nYour pin number is weak. Please choose a stronger pin." << endl;
            continue;
        } else {
            break;
        }
    }
    return Pin_number;
};


int main() {
    std::unordered_map<int, std::vector<std::string>> mp;
    std::unordered_map<int, Transaction_Record> transactions;
    if (sodium_init() == -1){
    std::cout << "Security initialization failed." << std::endl;
    return 1;
    }

    std::cout << "\n=====Welcome to Banking Management System=====" << endl;

    BankAccount account;


    LoadAccounts(mp, transactions);

    LoadTransactions(transactions);

    char hasAccount;
    std::cout<< "\n Do you have an account? (y/n): ";
    std::cin>> hasAccount;

    if (hasAccount == 'y' || hasAccount == 'Y') {
        if (!Login(mp)) {
            std::cout << "\nInvalid account number or pin. Exiting." << endl;
            SaveAccounts(mp);
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

            pin = GivePIN();

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
            SaveAccounts(mp);
            Savetransactions(transactions);
            break;
        }


        if (choice < 1 || choice > 6) {
            std::cout << "Invalid Choice" << endl;
            continue;
        }

        std::cout << "\nEnter the account number:";
        std::cin >> account_Number;

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