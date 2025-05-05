# 🏦 Banking Management System in C with Secure Binary Storage

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

A lightweight and modular command-line banking system developed in C. This project demonstrates key system-level concepts including binary file handling, modular architecture using header files, and persistent data management for core banking operations.

---

## 🚀 Features

- **👤 Account Lifecycle Management**  
  - Create and delete user accounts  
  - View account details and balance

- **💰 Core Banking Operations**  
  - Deposit and withdraw funds securely  
  - Transaction feedback and balance validation

- **🔐 Data Integrity and Security**  
  - Stores data in binary format to prevent tampering and accidental edits  
  - Prevents corruption by isolating read/write logic in a secure module

- **📁 Modular Structure**  
  - Business logic separated into `bankLib.c/.h`  
  - Easy to extend and test using external modules

- **🛠️ Makefile Build System**  
  - Automates compilation with object file management  
  - Easy to rebuild, clean, and debug

- **🧪 Test Automation**  
  - Includes `test.c` for unit testing core functionalities  
  - Enables regression checking before deployment

---

## 🧱 Architecture Overview

```bash
.
├── bank_main.c       # Main application logic and CLI
├── bankLib.c         # Core banking functions (CRUD ops, transactions)
├── bankLib.h         # Shared structures and function prototypes
├── test.c            # Test cases to validate logic
├── makeBank          # Executable (output)
├── data/             # Secure binary data storage
└── Makefile          # Build automation
```

---

## 📦 How It Works

1. **User launches the CLI tool**  
2. Chooses actions from a simple menu (Create, Deposit, Withdraw, Check Balance, etc.)  
3. System reads and writes data securely to a binary file under `data/`  
4. State is preserved across sessions and validated before each transaction

---

## 💻 Usage

### 1. Clone the Repository

```bash
git clone https://github.com/gitteja19/c-banking-system.git
cd c-banking-system
```

### 2. Compile the Code

```bash
make
```

### 3. Run the Program

```bash
./makeBank
```

---

## 📸 Sample Interface

```
===========================
      CLI BANK SYSTEM
===========================

1. Create Account
2. Deposit
3. Withdraw
4. Check Balance
5. View All Accounts
6. Exit
```

---

## 🛡 Security Notes

- Binary files are not human-readable, preventing accidental data corruption  
- Secure file access logic encapsulated in dedicated functions  
- Data structures validated before every operation

---

## 📈 Future Enhancements

- Role-based admin and user login access  
- Export transactions to CSV  
- Add interest calculation and scheduled deposits  
- Upgrade to SQLite or file-based database backend
---

## 📄 License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute it for educational and non-commercial purposes.
