#include <iostream>
using namespace std;

int main() {

    cout<<"Welcome to Banking Management System"<<endl;

    cout<<"\n=====Main Menu====="<<endl;

    cout<<"1. Create New Account"<<endl;
    cout<<"2. Deposit Amount"<<endl;
    cout<<"3. Withdraw Amount"<<endl;
    cout<<"4. Check Balance"<<endl;
    cout<<"5. Exit"<<endl;

    int choice;
    cout<<"\nEnter your choice: ";
    cin>>choice;

    cout<<"\nYou selected option: "<<choice<<endl;
    

    return 0;
}