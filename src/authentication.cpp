#include "../include/authentication.h"

#include <iostream>
#include <sodium.h>

bool activate(std::unordered_map<int, std::vector<std::string>>::iterator &it)
{
    const std::string &storedpin = it->second[3];

    int attempts = 0;
    int remaining = 3;
    std::string enteredpin;

    while (attempts < 3)
    {
        std::cout << "\nEnter the pin number:";
        std::cin >> enteredpin;

        if (crypto_pwhash_str_verify(
                storedpin.c_str(),
                enteredpin.c_str(),
                enteredpin.length()) == 0)
        {
            std::cout << "\nAccount is activated successfully.";
            it->second[4] = "Active";
            return true;
        }
        else
        {
            std::cout << "\nEntered wrong pin";
            remaining--;

            if (remaining != 0)
                std::cout << "\nRemaining attempts:" << remaining;

            attempts++;
        }
    }

    return false;
}

bool Login(std::unordered_map<int, std::vector<std::string>> &mp)
{
    std::string enteredpin;
    int account_number;

    std::cout << "\nEnter the account number:";
    std::cin >> account_number;

    auto it = mp.find(account_number);

    if (it == mp.end())
    {
        std::cout << "\nAccount Number does not exist." << std::endl;
        return false;
    }
    else if (it->second.size() < 5)
    {
        std::cout << "\nAccount data is incomplete." << std::endl;
        return false;
    }
    else if (it->second[4] == "Inactive")
    {
        std::cout << "\nAccount is locked.";

        char choice;

        std::cout << "\nDo you want to activate it(Enter y for Yes and n for No):";
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            return activate(it);
        }
        else if (choice == 'N' || choice == 'n')
        {
            return false;
        }
        else
        {
            std::cout << "\nInvalid choice";
            return false;
        }
    }
    else
    {
        std::cout << "\nYou have only 3 attempts to login if didn't able to login your account will be locked."
                  << std::endl;

        const std::string &storedhash = it->second[3];

        int attempts = 0;
        int remaining = 3;

        while (attempts < 3)
        {
            std::cout << "\nEnter the pin number:";
            std::cin >> enteredpin;

            if (crypto_pwhash_str_verify(
                    storedhash.c_str(),
                    enteredpin.c_str(),
                    enteredpin.length()) == 0)
            {
                return true;
            }

            remaining--;

            if (remaining != 0)
                std::cout << "\nRemaining attempts:" << remaining;

            attempts++;
        }
    }

    std::cout << "\nYou have exhausted your attempts.";
    std::cout << "\nLogin Failed";

    it->second[4] = "Inactive";

    return false;
}