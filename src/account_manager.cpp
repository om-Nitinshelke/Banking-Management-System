#include "../include/account_manager.h"

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