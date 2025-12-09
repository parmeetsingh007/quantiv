# Task 1 — Financial Transaction Ledger (C++)

### Overview
This program implements a financial transaction ledger using **Object-Oriented Programming** and **operator overloading** in C++.  
The project follows the requirements:
- `AbstractLedger` base class (pure virtual)
- Three derived classes:
  - `VectorLedger` (std::vector)
  - `LinkedListLedger` (custom linked list)
  - `ArrayLedger` (fixed-size C-array)
- Operator overloading:
  `+=`, `-=`, `==`, `!=`, `=`, `+`, `<<`

### Files
| Folder | Description |
|--------|-------------|
| task1 | All `.h` and `.cpp` files for the ledger system + main.cpp |

### How to Compile
g++ -std=c++17 main.cpp VectorLedger.cpp LinkedListLedger.cpp ArrayLedger.cpp -o task1

### How to run
./task1

### Sample Output
BUY AAPL 10
SELL GOOG 5
1
BUY AAPL 10
BUY AAPL 10
BUY AAPL 10
SELL GOOG 5
BUY AAPL 10
BUY TSLA 3
SELL GOOG 5
BUY TSLA 3
