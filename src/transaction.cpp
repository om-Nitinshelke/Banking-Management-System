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

void Transaction_Record::displayTransaction(const std::unordered_map<int, Transaction_Record> &transactions, int account_number) const {
    if (transaction_record.empty()) {
        std::cout << "No transactions yet" << std::endl;
        return;
    }

    std::cout << "\n=====Transaction History=====" << std::endl;
    std::cout << "Account Number: " << account << std::endl;

    for (Transaction record : transaction_record) {
        std::cout << record.type << " " << record.amount << std::endl;
    }
}

void Transaction_Record::saveTransactions(std::ostream &out) const {
    for (Transaction record : transaction_record) {
        out << account << " " << record.type << " " << record.amount << std::endl;
    }
}