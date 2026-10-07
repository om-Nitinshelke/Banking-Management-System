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