#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>
#include <ostream>
#include <unordered_map>


struct Transaction {
    std::string type;
    double amount;
};

class Transaction_Record {
private:
    int account;
    std::vector<Transaction> transaction_record;

public:
    Transaction_Record(int account_number);

    void addTransaction(std::string type, double amount);
    void displayTransaction(const std::unordered_map<int, Transaction_Record> &transactions, int account_number) const;
    void saveTransactions(std::ostream &out) const;
};

#endif