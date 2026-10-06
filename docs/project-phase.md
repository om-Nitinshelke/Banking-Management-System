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
- 9.3 Salting

     In this phase, the purpose and behavior of salting in password
     hashing were studied and verified.

     A salt is a randomly generated value used during password
     hashing. Its purpose is to ensure that the same PIN does not
     produce the same hash every time it is hashed.

     Libsodium's `crypto_pwhash_str()` was tested by hashing the same
     PIN multiple times.

     The same PIN produced different encoded hashes because a
     different random salt was generated for each hashing operation.

     The salt and the hashing parameters are included in the
     resulting encoded hash.

     Therefore, a separate salt field does not need to be created
     or stored manually when using Libsodium's high-level password
     hashing API.

     The generated hashes were then tested using
     `crypto_pwhash_str_verify()`.

     Both differently salted hashes successfully verified the same
     correct PIN.

     An incorrect PIN was also tested and verification returned a
     non-zero result, confirming that the incorrect PIN was rejected.

     The verification process was studied to understand how the
     stored hash is used.

     During verification, Libsodium obtains the salt and hashing
     parameters from the stored encoded hash and uses them to
     process the entered PIN before comparing the result with the
     stored hash.

     The application is responsible for identifying the account and
     providing that account's stored hash to Libsodium.

     Libsodium then verifies the entered PIN against that specific
     stored hash.

     No custom salt-generation mechanism was implemented because
     Libsodium already handles salt generation, storage, and use as
     part of its password hashing API.

- 9.4: Login Attempt Limiting

     A login attempt limit was implemented to prevent unlimited
     PIN verification attempts.

     The user is allowed a maximum of three login attempts during
     a login session.

     If the entered PIN is incorrect, the attempt counter is
     incremented and the user is allowed to try again.

     If the correct PIN is entered within the allowed attempts,
     authentication succeeds and the user is given access to the
     banking operations.

     If all three attempts are incorrect, authentication fails and
     access to the banking operations is denied.

     The current implementation limits attempts only for the
     current login session. It does not permanently lock the
     account or store the failed attempt count in the account file.

- 9.5 Account Lockout

     In this phase, an account lockout mechanism was implemented
     to prevent continued access after multiple failed login
     attempts.

     The login system already limited the user to three PIN
     verification attempts. After all three attempts failed, the
     account status was changed from `Active` to `Inactive`.

     The inactive status is stored in the account data structure
     along with the account information.

     The account data file was updated to store the account status,
     allowing the lockout state to persist after the program exits.

     During login, the account status is checked after finding the
     account.

     If the account status is `Inactive`, the login process is
     stopped immediately and the user is informed that the account
     is locked.

     No additional PIN attempts are allowed for an inactive account.

     The account itself is not deleted from the system. Its account
     information, balance, PIN hash, and transaction history remain
     stored.

     The lockout only prevents normal authentication and access to
     the banking operations.

     The account status is saved to `account.txt` when the login
     process fails after the maximum number of attempts.

     This ensures that restarting the program does not automatically
     remove the lockout.

     This phase introduced persistent account lockout as an
     additional security mechanism in the banking system.

- 9.6: Account Recovery and Unlocking

     In this phase, an account recovery and unlocking mechanism was
     implemented for accounts that have been locked after multiple
     failed login attempts.

     When the login process finds that an account has an `Inactive`
     status, the user is informed that the account is locked.

     The user is then given the option to activate the account again.

     If the user chooses not to activate the account, the login
     function returns `false` and access to the banking operations
     is denied.

     If the user chooses to activate the account, the account's
     stored PIN hash is retrieved from the account data.

     The user is given a maximum of three attempts to enter the
     correct PIN.

     The entered PIN is verified using Libsodium's
     `crypto_pwhash_str_verify()` function.

     The original PIN is never stored or recovered during this
     process. The entered PIN is verified against the stored PIN
     hash.

     If the correct PIN is entered within the three allowed
     attempts, the account status is changed from `Inactive` to
     `Active`.

     The activation function then returns `true`, allowing the
     `Login()` function to return `true` and grant access to the
     banking operations.

     If all three PIN attempts are incorrect, the activation process
     fails and the function returns `false`.

     The account remains inactive and access to the banking
     operations is denied.

     The account status is later written back to `account.txt` along
     with the other account information, allowing the activation
     status to persist after the program is restarted.

     This phase completes the basic account recovery and unlocking
     mechanism while reusing the existing PIN hashing and verification
     system.
- 9.7: Weak PIN Detection

     Implemented weak PIN detection to prevent users from choosing easily predictable PINs.

     Features:

     - Detects PINs containing the same repeated digit.
     - Detects ascending digit sequences.
     - Detects descending digit sequences.
     - Basic PIN validation remains in `main.cpp`.
     - Added a separate `PINStrength` class for PIN strength analysis.
     - Added `pin_strength.h` for class declarations.
     - Added `pin_strength.cpp` for the implementation of PIN strength checks.

     Weak PIN Examples:

     - `1111` → Repeated digits
     - `7777` → Repeated digits
     - `1234` → Ascending sequence
     - `4321` → Descending sequence
     - `5656755` ->Excessive digit frequency

     The PIN is checked for these weak patterns before it is hashed and stored.

## Phase 10: Project Architecture & Separation of Responsibilities

- Phase 10.1:Separate BankAccount

     - Separated the `BankAccount` class from `main.cpp`.
     - Created `include/bank_account.h` to contain the class declaration and function prototypes.
     - Created `src/bank_account.cpp` to contain the implementations of:
     - `deposit()`
     - `withDraw()`
     - `displayAccount()`
     - Updated `main.cpp` to include `bank_account.h`.
     - Kept the existing account operation logic unchanged while improving project structure.
     - This separation makes the code easier to maintain and prepares the project for further architectural improvements in Phase 10.
