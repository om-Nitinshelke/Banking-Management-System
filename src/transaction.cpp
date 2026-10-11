#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "../include/transaction.h"

Transaction_Record::Transaction_Record(int account_number) {
    account = account_number;
}

void Transaction_Record::addTransaction(std::string type, double amount) {
    transaction_record.push_back({type, amount});
}

void Transaction_Record::displayTransaction(
    const std::unordered_map<int, Transaction_Record> &transactions,
    int account_number
) const {
    auto it = transactions.find(account_number);
    if (it == transactions.end()) {
        std::cout << "Account not found" << std::endl;
        return;
    }

    const auto &record = it->second;

    if (record.transaction_record.empty()) {
        std::cout << "No transactions yet" << std::endl;
        return;
    }

    std::cout << "\n=====Transaction History=====" << std::endl;
    std::cout << "Account Number: " << account_number << std::endl;

    for (const auto &t : record.transaction_record) {
        std::cout << t.type << " " << t.amount << std::endl;
    }
}

void Transaction_Record::saveTransactions(std::ostream &out) const {
    for (const auto &record : transaction_record) {
        out << account << " " << record.type << " " << record.amount << std::endl;
    }
}