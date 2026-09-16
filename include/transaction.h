#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <string>

using namespace std;

class Transaction_Record {
private:
    int account;
    vector<string> transaction_record;

public:
    Transaction_Record(int account_number);
    void addTransaction(string record);
    void displayTransaction() const;
};

#endif