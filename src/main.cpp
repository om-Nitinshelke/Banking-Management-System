#include <iostream>
#include<sodium.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "../include/transaction.h"
#include "../include/pin_strength.h"
#include "../include/bank_account.h"
#include "../include/authentication.h"
#include "../include/account_manager.h"



int main() {
    std::unordered_map<int, std::vector<std::string>> mp;
    std::unordered_map<int, Transaction_Record> transactions;
    if (sodium_init() == -1){
    std::cout << "Security initialization failed." << std::endl;
    return 1;
    }

    std::cout << "\n=====Welcome to Banking Management System=====" << std::endl;

    BankAccount account;


    LoadAccounts(mp, transactions);

    LoadTransactions(transactions);

    char hasAccount;
    std::cout<< "\n Do you have an account? (y/n): ";
    std::cin>> hasAccount;
    std::pair<bool, int> login_result;

    if (hasAccount == 'y' || hasAccount == 'Y') {
        login_result = Login(mp);
        if (!login_result.first) {
            std::cout << "\nInvalid account number or pin. Exiting." <<std::endl;
            SaveAccounts(mp);
            return 1;
        }
    } else if (hasAccount == 'n' || hasAccount == 'N') {
        std::cout << "\nPlease create an account first." << std::endl;
        std::cout<< "\nDo you want to create an account? (y/n): ";
        char createAccountChoice;
        std::cin >> createAccountChoice;
        int account_number;
        if (createAccountChoice == 'y' || createAccountChoice == 'Y') {
            account_number = CreateAccount(mp, transactions);
            if (!account_number) {
                std::cout << "\nAccount creation failed. Exiting." <<std::endl;
                SaveAccounts(mp);
                return 1;
            }
            login_result = std::make_pair(true, account_number);
        } else {
            std::cout << "\nAccount creation declined. Exiting." << std::endl;
            SaveAccounts(mp);
            return 1;
        }
    } else {
        std::cout << "\nInvalid input. Exiting." << std::endl;
        return 1;
    }


    while (true) {
        std::cout << "\n=====Main Menu=====" <<std::endl;
        std::cout << "1. Deposit Money" << std::endl;
        std::cout << "2. WithDraw Money" << std::endl;
        std::cout << "3. Check Account" << std::endl;
        std::cout << "4. Transaction History" << std::endl;
        std::cout << "5. Exit" << std::endl;

        int choice;

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 5) {
            std::cout << "Thanks for using Banking Management System" <<std::endl;
            SaveAccounts(mp);
            Savetransactions(transactions);
            break;
        }


        if (choice < 1 || choice > 5) {
            std::cout << "Invalid Choice" << std::endl;
            continue;
        }


        switch (choice) {
            case 1: {
                double amount;

                std::cout << "\nEnter the amount: ";
                std::cin >> amount;

                double current_balance = 0.0;
                try {
                    current_balance = account.deposit(
                        amount,
                        mp,
                        login_result.second,
                        transactions.at(login_result.second)
                    );
                } catch (const std::out_of_range &e) {
                    std::cout << "Exception: Account not found in transaction records - " << e.what() <<std::endl;
                    continue;
                }

                if (current_balance) {
                    std::cout << "The amount is deposited successfully. The current balance is: "
                         << current_balance <<std::endl;
                } else {
                    std::cout << "Amount should be greater than 0. Deposit unsuccessful." <<std::endl;
                }

                break;
            }

            case 2: {
                double amount;

                std::cout << "\nEnter the amount to withDraw: ";
                std::cin >> amount;

                if (amount <= 0) {
                    std::cout << "The amount should be greater than 0" <<std::endl;
                } else {
                    try {
                        account.withDraw(
                            amount,
                            mp,
                            login_result.second,
                            transactions.at(login_result.second)
                        );
                    } catch (const std::out_of_range &e) {
                        std::cout << "Exception: Account not found in transaction records - " << e.what() <<std::endl;
                    }
                }

                break;
            }

            case 3: {
                account.displayAccount(mp, login_result.second);
                break;
            }

           case 4: {
            try {
                transactions.at(login_result.second).displayTransaction();
            } catch (const std::out_of_range &e) {
                std::cout << "Exception: Account not found in transaction records - " << e.what() <<std::endl;
            }
            break;
           }

            
        }
    }

    return 0;
}