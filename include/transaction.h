#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>
#include <ostream>

using namespace std;

struct Transaction {
    string type;
    double amount;
};

class Transaction_Record {
private:
    int account;
    vector<Transaction> transaction_record;

public:
    Transaction_Record(int account_number);

    void addTransaction(string type, double amount);
    void displayTransaction() const;
    void saveTransactions(ostream &out) const;
};

#endif