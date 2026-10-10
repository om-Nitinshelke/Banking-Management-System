#include "../include/account_manager.h"
#include "../include/pin_strength.h"
#include <sodium.h>

#include <fstream>
#include <iostream>

void LoadAccounts(
    std::unordered_map<int, std::vector<std::string>> &mp,
    std::unordered_map<int, Transaction_Record> &transactions
)
{
    std::ifstream file("data/account.txt");

    if (!file)
    {
        std::cout << "Error: Unable to open account data file."
                  << std::endl;
        return;
    }

    int accountNumber;
    std::string name;
    std::string surname;
    std::string balance;
    std::string pin_number;
    std::string account_status;

    while (file >> accountNumber
                >> name
                >> surname
                >> balance
                >> pin_number
                >> account_status)
    {
        mp[accountNumber] = {
            name,
            surname,
            balance,
            pin_number,
            account_status
        };

        transactions.emplace(
            accountNumber,
            Transaction_Record(accountNumber)
        );
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


std::string GivePIN() {
    std::string Pin_number;
    PINStrength pinChecker;

    while (true) {
        cout << "\nEnter the pin number(atmost there should be 8 digits):";
        cin >> Pin_number;
        if (Pin_number.length() < 4) {
            cout << "\nThere should be atleast 4 digits";
            continue;
        } else if (Pin_number.length() > 8) {
            cout << "\nThere should be atmost 8 digits";
            continue;
        } else if (Pin_number.length() <= 8) {
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

bool CreateAccount(std::unordered_map<int, std::vector<std::string>> &mp,std::unordered_map<int, Transaction_Record> &transactions) {
    std::string name;
    std::string surname;
    int account_number;
    double amount;
    std::string pin;

    std::cout << "\nEnter your name: ";
    std::cin >> name;

    std::cout << "\nEnter your surname: ";
    std::cin >> surname;

    std::cout << "\nEnter your account number: ";
    std::cin >> account_number;

    if (account_number <= 0) {
        std::cout << "Account number should be positive" << std::endl;
        return false;
    }

    if (mp.find(account_number) != mp.end()) {
        std::cout << "Account already exists" << std::endl;
        return false;
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
                std::cout<<"\nPIN hashing failed" << std::endl;
                return false;
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
        std::cout << "Account created successfully" << std::endl;
        return true;
    }
    return false;   
}