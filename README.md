#Banking Management System

A C++ Banking Managment System built as a learning project to practice C++ programming, OOP, STL, and file handling

##Project Status

# Banking Management System — Project Phases

## Phase 1: Basic C++ and Menu

- Learned basic C++ syntax and program structure.
- Implemented variables and data types.
- Used `cin` and `cout`.
- Implemented the basic banking menu.
- Practiced conditional statements and loops.

## Phase 2: Classes and Objects

- Created the `BankAccount` class.
- Used private data members.
- Implemented constructors.
- Implemented member functions.
- Practiced encapsulation and OOP.

## Phase 3: Account Operations

- Implemented deposit and withdrawal operations.
- Added minimum balance validation.
- Added validation for invalid transaction amounts.
- Used `const` member functions where appropriate.

## Phase 4: Multiple Account Management

- Extended the system to support multiple accounts.
- Used `unordered_map`.
- Used account number as the key.
- Stored account information as the associated value.

## Phase 5: File Handling and Data Persistence

- Implemented `ifstream` and `ofstream`.
- Loaded account information from `data/account.txt`.
- Stored loaded data in the in-memory data structure.
- Updated account information during execution.
- Saved updated account information back to the file when exiting.

## Phase 6: Transaction Management

- Created the `Transaction_Record` class.
- Created `transaction.h` and `transaction.cpp`.
- Added transaction history using `vector<string>`.
- Used `unordered_map<int, Transaction_Record>` for transaction records.
- Integrated transaction recording with deposits and withdrawals.
- Added transaction history viewing.
- Implemented persistent transaction storage.
- Loaded transaction history from `data/transactions.txt` when the program starts.
- Stored transaction information in memory during execution.
- Saved updated transaction history back to the file when the program exits.

## Phase 7: Exception Handling and Input Validation

- Implemented input validation throughout the system.
- Added handling for invalid user inputs.
- Added validation for invalid transaction amounts.
- Added validation for invalid menu choices.
- Implemented exception handling using `try`, `throw`, and `catch`.
- Added handling for unexpected errors during program execution.
- Improved the system's ability to handle invalid input without terminating unexpectedly.
- Improved the overall reliability and robustness of the banking system.

## Phase 8: Authentication

- Implemented a login system for the banking application.
- Added account number and PIN-based authentication.
- Updated account data to include a PIN for each account.
- Updated account data loading to read the PIN along with the existing account information.
- Implemented account number verification during login.
- Implemented PIN verification for the corresponding account.
- Added validation to check whether the entered account number exists.
- Prevented access to banking operations when the account number does not exist.
- Prevented access to banking operations when the entered PIN does not match the stored PIN.
- Allowed access to the banking menu only after successful authentication.
- Added appropriate messages for invalid account numbers and incorrect PINs.
- Integrated the authentication process with the existing account data structure.
- Controlled access to banking operations based on the authentication result.

## Phase 9: Security

- 🔄 Phase currently in progress.


## Features

- Create a bank account
- Store multiple accounts
- Deposit money
- Withdraw money
- Check account details
- Minimum balance validation
- Account data persistence using files
- Transaction history tracking
- Transaction history persistence
- Load transaction history when the program starts
- Save transaction history when the program exits
- Input validation
- Exception handling
- Handling invalid user input
- Handling unexpected errors

## Technologies and Concepts

- C++
- Object-Oriented Programming
- Classes and Objects
- Encapsulation
- STL
- `unordered_map`
- `vector`
- File Handling
- `ifstream`
- `ofstream`
- Header and Implementation Files
- Constructors
- Member Functions
- Basic Input Validation
- Transaction Management
- Exception Handling and input validation


## Project Structure

```text
Banking-Management-System/
├── README.md
├── .gitignore
├── include/
│   └── transaction.h
├── src/
│   ├── main.cpp
│   └── transaction.cpp
├── data/
│   ├── account.txt
│   └── transactions.txt
└── docs/
     └── project-phases.md




