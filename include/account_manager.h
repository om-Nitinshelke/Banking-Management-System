#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "transaction.h"

void LoadAccounts(
    std::unordered_map<int, std::vector<std::string>> &mp,
    std::unordered_map<int, Transaction_Record> &transactions
);

void LoadTransactions(std::unordered_map<int, Transaction_Record> &transactions);

void SaveAccounts(const std::unordered_map<int, std::vector<std::string>> &mp);

void Savetransactions(const std::unordered_map<int, Transaction_Record> &transactions);

std::string GivePIN();

#endif