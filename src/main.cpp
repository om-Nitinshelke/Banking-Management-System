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

    int deposit(double amount) {

        if (amount <=  0) return 0;
        balance += amount;

        return balance;
    }

    void withDraw(double amount) {

        if (amount > balance) {
            cout<<"Insufficient balance"<<endl;
        }else if (balance-amount < 500) {
            cout<<"After withdrawing this amount the balance will be less than 500 rupees hence according rules of the bank there should be alleast 500 rupees in the balance"<<endl;
        }else if (amount <= balance) {
            balance -= amount;
            cout<<"The withdraw was successful the current balance is:"<<balance<<endl;
        } 
        return ;
    }

    void displayAccount() const {
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
    cout<<"3.Check Account"<<endl;
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
            int current_balance=account.deposit(amount);

            if (current_balance) {
                cout<<"The amount is deposited successfully the current balance is:"<<current_balance<<endl;
            } else {
                cout<<"You're amount was smaller than 0 deposition becomes unsuccessful"<<endl;
            }
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