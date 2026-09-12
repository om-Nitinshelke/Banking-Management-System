#include <iostream>
#include <string>
using namespace std;


class BankAccount {
private:
    string name;
    int accountNumber;
    double balance;

public:
    BankAccount(string name,int accountNumber,double balance) {
        this->name=name;
        this->accountNumber=accountNumber;
        this->balance=balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withDraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout<<"Insufficient balance"<<endl;
        }
    }

    void displayAccount() {
        cout<<"\n=====Account Details====="<<endl;
        cout<<"Name:"<<name<<endl;
        cout<<"Account Number:"<<accountNumber<<endl;
        cout<<"Balance:"<<balance<<endl;
    }

};

int main() {

    cout<<"\n=====Welcome to Banking Management System====="<<endl;

    string name;
    int accountNumber;
    double balance;

    cout<<"\nEnter your name:";
    getline(cin,name);
    cout<<"\nEnter the account number:";
    cin>>accountNumber;
    cout<<"\nEnter the current balance";
    cin>>balance;


    BankAccount account(name,accountNumber,balance);


    cout<<"\n=====Main Menu====="<<endl;
    cout<<"1.Deposit Money"<<endl;
    cout<<"2.WithDraw Money"<<endl;
    cout<<"3.Check Amount"<<endl;
    cout<<"4.Exit"<<endl;


    while (true) {
       int choice;

       cout<<"\nEnter your choice:";
       cin>>choice;

       switch (choice) {
        case 1: {
            double amount;
            cout<<"\nEnter the amount:";
            cin>>amount;
            account.deposit(amount);
            cout<<"\nAmount Deposited Successfully"<<endl;
            break;

        }

        case 2: {
            double amount;
            cout<<"\nEnter the amount to withDraw:"<<endl;
            cin>>amount;
            account.withDraw(amount);
            break;
        }

        case 3: {
            account.displayAccount();
            break;
        }

        case 4: {
            cout<<"Thanks for using Banking Managment System"<<endl;
            break;
        }

        default:
          cout<<"Invlid Choice"<<endl;  
       }

       if (choice==4)
        break;
    }
    
    return 0;
}