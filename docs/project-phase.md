# Banking Management System — Project Phases

## Phase 1: Basic C++ and Menu
- Learned basic C++ syntax and program structure.
- Implemented variables and data types.
- Used `cin` and `cout` for user input and output.
- Implemented the basic banking menu.
- Practiced conditional statements and loops.

## Phase 2: Classes and Objects
- Introduced the `BankAccount` class.
- Implemented private data members for account information.
- Used constructors to initialize account objects.
- Implemented member functions for account operations.
- Practiced encapsulation and object-oriented programming.

## Phase 3: Account Operations
- Implemented deposit and withdrawal operations.
- Added balance validation.
- Added a minimum balance requirement.
- Added validation for invalid transaction amounts.
- Used `const` member functions where appropriate.

## Phase 4: Multiple Account Management
- Extended the system to handle multiple accounts.
- Used an STL map to store account information.
- Used the account number as the key.
- Stored account name and balance as the associated data.
- Implemented operations for working with multiple accounts.

## Phase 5: File Handling and Data Persistence
- Implemented file handling using `ifstream` and `ofstream`.
- Account data is loaded from `data/account.txt` when the program starts.
- Loaded account information is stored in the in-memory data structure.
- Account operations modify the data structure during program execution.
- Updated account data is written back to the file when the user exits.
- Implemented persistent storage so account data remains available between program runs.

## Phase 6: Transaction Management

- 🔄 Phase currently in progress.
- Created a separate `Transaction_Record` class.
- Created `transaction.h` for class declarations.
- Created `transaction.cpp` for class implementations.
- Added a transaction history using `vector<string>`.
- Associated transaction records with account numbers.
- Integrated transaction recording with deposit operations.
- Integrated transaction recording with withdrawal operations.
- Added transaction history viewing.
- Transaction history is currently stored only in memory.
- Transaction persistence to a file is planned.