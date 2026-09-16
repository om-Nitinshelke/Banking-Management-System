#include "../include/transaction.h"
#include <iostream>

using namespace std;

Transaction_Record::Transaction_Record(int account_number) {
    account = account_number;
}

void Transaction_Record::addTransaction(string record) {
    transaction_record.push_back(record);
}

void Transaction_Record::displayTransaction() const {
    if (transaction_record.empty()) {
        cout << "No transactions yet" << endl;
        return;
    }

    cout << "\n=====Transaction History=====" << endl;
    cout << "Account Number: " << account << endl;

    for (string record : transaction_record) {
        cout << record << endl;
    }
}