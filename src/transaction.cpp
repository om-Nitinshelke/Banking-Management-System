#include "../include/transaction.h"
#include <iostream>

using namespace std;

Transaction_Record::Transaction_Record(int account_number) {
    account = account_number;
}

void Transaction_Record::addTransaction(string type, double amount) {
    transaction_record.push_back({type, amount});
}

void Transaction_Record::displayTransaction() const {
    if (transaction_record.empty()) {
        cout << "No transactions yet" << endl;
        return;
    }

    cout << "\n=====Transaction History=====" << endl;
    cout << "Account Number: " << account << endl;

    for (Transaction record : transaction_record) {
        cout << record.type << " " << record.amount << endl;
    }
}

void Transaction_Record::saveTransactions(ostream &out) const {
    for (Transaction record : transaction_record) {
        out << account << " " << record.type << " " << record.amount << endl;
    }
}