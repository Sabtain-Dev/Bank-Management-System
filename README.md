# Bank Management System - C++ Project

## Overview
This is a console-based Bank Management System implemented in C++. It allows users to perform various banking operations such as creating accounts, depositing/withdrawing funds, transferring money between accounts, and managing account information.

## Features
- **Account Management**:
  - Create new bank accounts
  - Delete existing accounts
  - Search for accounts
  - Display all accounts
  - Sort accounts by account number

- **Financial Operations**:
  - Deposit money
  - Withdraw money (with withdrawal charges)
  - Transfer money between accounts (with transfer charges)

- **Security**:
  - Password protection for accounts
  - Secure password input (hidden with asterisks)
  - Validation for all inputs

- **Data Persistence**:
  - Accounts are saved to "accounts.txt" file
  - Data is automatically loaded when program starts

## Technical Details
- Implemented using C++ with OOP principles
- Uses a doubly-linked list to store account data
- File I/O for data persistence
- Input validation for all user inputs
- Secure password handling
- Error handling for various scenarios

## How to Use
1. Compile the program using a C++ compiler (tested with g++)
2. Run the executable
3. Use the menu to navigate through different banking operations
4. Follow on-screen instructions for each operation

## Requirements
- C++ compiler (g++, clang++, etc.)
- Standard C++ libraries
- Windows (for `conio.h` - can be replaced for other platforms)

## File Structure
- `main.cpp` - Contains all the implementation
- `accounts.txt` - Data file created automatically to store account information

## Future Improvements
- Add interest calculation for savings accounts
- Implement transaction history
- Add admin/user roles
- Enhance UI with colors and better formatting
- Add more account types and features

## Notes
- The program uses Windows-specific `conio.h` for password hiding
- For Linux/Mac, alternative methods would be needed for password hiding
- All data is stored in plain text - not suitable for production use without encryption
