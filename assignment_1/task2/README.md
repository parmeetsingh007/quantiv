# Task 2 — Boolean Circuit Simulator (C++)

### Overview
This program implements a Boolean logic simulator using:
- `Gate` abstract base class
- Derived gates: `AND, OR, XOR, NAND, NOR, XNOR`
- `Circuit` class containing a sequence of gates
- `Input` struct using **Singleton Pattern** (`T()` and `F()` only instances)

### Requirements Covered
| Requirement | Status |
|------------|--------|
| Gate abstract base class | ✔ |
| Evaluate in gate + circuit | ✔ |
| Singleton Inputs T and F | ✔ |
| Test cases in driver (main.cpp) | ✔ |

### How to Compile
g++ -std=c++17 main.cpp Circuit.cpp Gates.cpp -o task2

### How to Run
./task2

### Sample Output
Test 1 (((T AND T) OR F) XOR T) = 0
Test 2 (T NAND F, NOR T, XNOR T) = 0
Test 3 (F OR T) = 1