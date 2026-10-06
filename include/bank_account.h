#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <unordered_map>
#include <vector>

#include "transaction.h"

class BankAccount
{
public:
    double deposit(
        double amount,
        std::unordered_map<int, std::vector<std::string>> &mp,
        int account_Number,
        Transaction_Record &transaction
    );

    void withDraw(
        double amount,
        std::unordered_map<int, std::vector<std::string>> &mp,
        int account_Number,
        Transaction_Record &transaction
    );

    void displayAccount(
        std::unordered_map<int, std::vector<std::string>> &mp,
        int account_Number
    ) const;
};

#endif