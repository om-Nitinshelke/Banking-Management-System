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

    std::cout << "\n=====Welcome to Banking Management System=====" << endl;

    BankAccount account;


    LoadAccounts(mp, transactions);

    LoadTransactions(transactions);

    char hasAccount;
    std::cout<< "\n Do you have an account? (y/n): ";
    std::cin>> hasAccount;

    if (hasAccount == 'y' || hasAccount == 'Y') {
        if (!Login(mp)) {
            std::cout << "\nInvalid account number or pin. Exiting." << endl;
            SaveAccounts(mp);
            return 1;
        }
    } else if (hasAccount == 'n' || hasAccount == 'N') {
        std::cout << "\nPlease create an account first." << endl;
    } else {
        std::cout << "\nInvalid input. Exiting." << endl;
        return 1;
    }

    while (true) {
        std::cout << "\n=====Main Menu=====" << endl;
        std::cout << "1. Deposit Money" << endl;
        std::cout << "2. WithDraw Money" << endl;
        std::cout << "3. Check Account" << endl;
        std::cout << "4. Create Account" << endl;
        std::cout << "5. Transaction History" << endl;
        std::cout << "6. Exit" << endl;

        int choice;
        int account_Number;

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (choice == 4) {
            string name;
            string surname;
            int account_number;
            double amount;
            string pin;

            std::cout << "\nEnter your name: ";
            std::cin >> name;

            std::cout << "\nEnter your surname: ";
            std::cin >> surname;

            std::cout << "\nEnter your account number: ";
            std::cin >> account_number;

            if (account_number <= 0) {
                std::cout << "Account number should be positive" << endl;
                continue;
            }

            if (mp.find(account_number) != mp.end()) {
                std::cout << "Account already exists" << endl;
                continue;
            }

            std::cout << "\nEnter the amount for first deposit. Minimum amount is 500: ";
            std::cin >> amount;

            pin = GivePIN();

            size_t pin_length = pin.length();
            char hashed_pin[crypto_pwhash_STRBYTES]; 

            if (crypto_pwhash_str(
                hashed_pin,
                pin.c_str(),
                pin_length,
                crypto_pwhash_OPSLIMIT_INTERACTIVE,
                crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
                std::cout<<"\nPIN hashing failed" << endl;
                continue;
            }
            string storedHash = hashed_pin;
            

            if (amount < 500) {
                std::cout << "Minimum amount should be 500" << endl;
            } else {
                mp[account_number] = {name, surname, to_string(amount),storedHash, "Active"};

                auto result = transactions.emplace(
                    account_number,
                    Transaction_Record(account_number)
                );

                result.first->second.addTransaction("InitialDeposit", amount);

                std::cout << "Account created successfully" << endl;
            }

            continue;
        }

        if (choice == 6) {
            std::cout << "Thanks for using Banking Management System" << endl;
            SaveAccounts(mp);
            Savetransactions(transactions);
            break;
        }


        if (choice < 1 || choice > 6) {
            std::cout << "Invalid Choice" << endl;
            continue;
        }

        std::cout << "\nEnter the account number:";
        std::cin >> account_Number;

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
                        account_Number,
                        transactions.at(account_Number)
                    );
                } catch (const out_of_range &e) {
                    std::cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                    continue;
                }

                if (current_balance) {
                    std::cout << "The amount is deposited successfully. The current balance is: "
                         << current_balance << endl;
                } else {
                    std::cout << "Amount should be greater than 0. Deposit unsuccessful." << endl;
                }

                break;
            }

            case 2: {
                double amount;

                std::cout << "\nEnter the amount to withDraw: ";
                std::cin >> amount;

                if (amount <= 0) {
                    std::cout << "The amount should be greater than 0" << endl;
                } else {
                    try {
                        account.withDraw(
                            amount,
                            mp,
                            account_Number,
                            transactions.at(account_Number)
                        );
                    } catch (const out_of_range &e) {
                        std::cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                    }
                }

                break;
            }

            case 3: {
                account.displayAccount(mp, account_Number);
                break;
            }

            case 5: {
                try {
                    transactions.at(account_Number).displayTransaction();
                } catch (const out_of_range &e) {
                    std::cout << "Exception: Account not found in transaction records - " << e.what() << endl;
                }
                break;
            }
        }
    }

    return 0;
}