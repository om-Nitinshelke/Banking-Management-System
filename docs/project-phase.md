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

- Implemented transaction management for bank accounts.
- Created a separate `Transaction_Record` class.
- Created `transaction.h` for class declarations.
- Created `transaction.cpp` for class implementations.
- Added transaction history using `vector<string>`.
- Associated transaction records with account numbers.
- Used `unordered_map<int, Transaction_Record>` to manage transaction history for multiple accounts.
- Integrated transaction recording with deposit operations.
- Integrated transaction recording with withdrawal operations.
- Added transaction history viewing.
- Implemented transaction persistence using file handling.
- Transaction history is loaded from `data/transactions.txt` when the program starts.
- Transaction history is stored in memory during program execution.
- Updated transaction history is written back to `data/transactions.txt` when the program exits.

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

-  9.1:Security Fundamentals
-  9.2: PIN Hashing

     In this phase, PIN hashing was implemented to avoid storing
     user PINs in plaintext.

     Libsodium was integrated into the project and Argon2id-based
     password hashing was used.

     During account creation, the entered PIN is passed to
     `crypto_pwhash_str()`. The resulting hash is stored instead
     of the original PIN.

     During authentication, the entered PIN is verified against
     the stored hash using `crypto_pwhash_str_verify()`.

     The verification process does not decrypt the stored hash.
     Instead, the hashing parameters and salt contained in the
     stored hash are used to verify whether the entered PIN
     matches the original PIN.

     This ensures that the account data file does not contain
     plaintext PINs.