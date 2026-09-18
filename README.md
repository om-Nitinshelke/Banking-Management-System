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

## Phase 7: Input Validation and Error Handling

- 🔄 Phase currently in progress.





