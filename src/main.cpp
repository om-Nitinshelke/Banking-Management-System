#include <iostream>
#include <string>
#include<unordered_map>
#include<vector>
#include<cstdlib>
#include<cctype>
using namespace std;


class BankAccount {
public:

    int deposit(double amount,unordered_map<int,vector<string>> &mp,int account_Number) {

        if (amount <= 0) return 0;
        int balance=stoi(mp[account_Number][1]);

        balance += amount;

        mp[account_Number][1]=to_string(balance);

        return balance;
        
    }

    void withDraw(double amount,unordered_map<int,vector<string>> &mp,int account_Number) {
        int balance=stoi(mp[account_Number][1]);


        if (amount > balance) {
            cout<<"Insufficient balance"<<endl;
        }else if (balance-amount < 500) {
            cout<<"After withdrawing this amount the balance will be less than 500 rupees hence according rules of the bank there should be alleast 500 rupees in the balance"<<endl;
        }else if (amount <= balance) {
            balance -= amount;
            mp[account_Number][1]=to_string(balance);

            cout<<"The withdraw was successful the current balance is:"<<balance<<endl;
        } 
        return ;
    }

    void displayAccount(unordered_map<int,vector<string>> &mp,int account_Number) const {
        cout<<"\n=====Account Details====="<<endl;
        cout<<"Name:"<<mp[account_Number][0]<<endl;
        cout<<"Account Number:"<<account_Number<<endl;
        cout<<"Balance:"<<mp[account_Number][1]<<endl;
    }

};

int main() {

    unordered_map<int, vector<string>> mp;

    cout << "\n=====Welcome to Banking Management System=====" << endl;

    cout << "\n=====Main Menu=====" << endl;
        cout << "1.Deposit Money" << endl;
        cout << "2.WithDraw Money" << endl;
        cout << "3.Check Account" << endl;
        cout << "4.Create Account" << endl;
        cout << "5.Exit" << endl;

    BankAccount account;

    while (true) {

        int choice;
        int account_Number;

        cout << "\nEnter your choice:";
        cin >> choice;

        if (choice == 4) {
            string name;
            int account_number;
            int amount;

            cin.ignore();

            cout << "\nEnter your name:";
            getline(cin, name);

            cout << "\nEnter your account number:";
            cin >> account_number;

            if (mp.find(account_number) != mp.end()) {
                cout << "Account already exists" << endl;
                continue;
            }

            cout << "\nEnter the amount for first deposit the minimum amount is 500:";
            cin >> amount;

            if (amount < 500) {
                cout << "Minimum amount should be 500" << endl;
            } else {
                mp[account_number] = {name, to_string(amount)};
                cout << "Account created successfully" << endl;
            }

            continue;
        }

        if (choice == 5) {
            cout << "Thanks for using Banking Managment System" << endl;
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid Choice" << endl;
            continue;
        }

        cout << "\nEnter your account number:";
        cin >> account_Number;

        if (mp.find(account_Number) == mp.end()) {
            cout << "\nYou don't have account here first make the account" << endl;
            continue;
        }

        switch (choice) {

            case 1: {
                double amount;
                cout << "\nEnter the amount:";
                cin >> amount;

                int current_balance = account.deposit(amount, mp, account_Number);

                if (current_balance) {
                    cout << "The amount is deposited successfully the current balance is:" << current_balance << endl;
                } else {
                    cout << "Your amount was smaller than 0 deposition becomes unsuccessful" << endl;
                }

                break;
            }

            case 2: {
                double amount;
                cout << "\nEnter the amount to withDraw:";
                cin >> amount;

                account.withDraw(amount, mp, account_Number);
                break;
            }

            case 3: {
                account.displayAccount(mp, account_Number);
                break;
            }
        }
    }

    return 0;
}