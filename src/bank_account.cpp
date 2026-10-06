#include "../include/bank_account.h"

#include <iostream>
#include <stdexcept>

double BankAccount::deposit(double amount,std::unordered_map<int, std::vector<std::string>> &mp,int account_Number,
    Transaction_Record &transaction
)
{
    if (amount <= 0)
        return 0;

    auto it = mp.find(account_Number);

    if (it == mp.end() || it->second.size() < 5)
    {
        std::cout << "Invalid account data for account "
                  << account_Number << std::endl;
        return 0;
    }

    double balance = 0.0;

    try
    {
        balance = std::stod(it->second[2]);
    }
    catch (const std::invalid_argument &)
    {
        std::cout << "Invalid balance format for account "
                  << account_Number << std::endl;
        return 0;
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Balance value is out of range for account "
                  << account_Number << std::endl;
        return 0;
    }

    balance += amount;
    it->second[2] = std::to_string(balance);

    transaction.addTransaction("Deposit", amount);

    return balance;
}


void BankAccount::withDraw(
    double amount,
    std::unordered_map<int, std::vector<std::string>> &mp,
    int account_Number,
    Transaction_Record &transaction
)
{
    auto it = mp.find(account_Number);

    if (it == mp.end() || it->second.size() < 5)
    {
        std::cout << "Invalid account data for account "
                  << account_Number << std::endl;
        return;
    }

    double balance = 0.0;

    try
    {
        balance = std::stod(it->second[2]);
    }
    catch (const std::invalid_argument &)
    {
        std::cout << "Invalid balance format for account "
                  << account_Number << std::endl;
        return;
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Balance value is out of range for account "
                  << account_Number << std::endl;
        return;
    }

    if (amount > balance)
    {
        std::cout << "Insufficient balance" << std::endl;
    }
    else if (balance - amount < 500)
    {
        std::cout << "After withdrawing this amount the balance will be less than 500 rupees."
                  << std::endl;

        std::cout << "According to bank rules, at least 500 rupees should remain in the account."
                  << std::endl;
    }
    else
    {
        balance -= amount;
        it->second[2] = std::to_string(balance);

        transaction.addTransaction("WithDraw", amount);

        std::cout << "The withdraw was successful. The current balance is: "
                  << balance << std::endl;
    }
}

void BankAccount::displayAccount(
    std::unordered_map<int, std::vector<std::string>> &mp,
    int account_Number
) const
{
    auto it = mp.find(account_Number);

    if (it == mp.end())
    {
        std::cout << "Account number does not exist" << std::endl;
        return;
    }

    if (it->second.size() < 5)
    {
        std::cout << "Account data is incomplete" << std::endl;
        return;
    }

    std::cout << "\n=====Account Details=====" << std::endl;
    std::cout << "Name: " << it->second[0]
              << " " << it->second[1] << std::endl;
    std::cout << "Balance: " << it->second[2] << std::endl;
}