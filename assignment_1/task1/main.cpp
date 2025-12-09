#include <iostream>
#include "VectorLedger.h"
#include "LinkedListLedger.h"
#include "ArrayLedger.h"

int main() {
    Transaction t1("BUY", "AAPL", 10);
    Transaction t2("SELL", "GOOG", 5);
    Transaction t3("BUY", "TSLA", 3);

    VectorLedger v1;
    v1 += t1;
    v1 += t2;

    VectorLedger v2;
    v2 += t1;
    v2 += t2;

    std::cout << v1;
    std::cout << (v1 == v2) << "\n";

    v1 -= 1;
    std::cout << v1;

    AbstractLedger *v3 = v1 + v2;
    std::cout << *v3;
    delete v3;

    LinkedListLedger l1;
    l1 += t1;
    l1 += t3;
    std::cout << l1;

    ArrayLedger a1;
    a1 += t2;
    a1 += t3;
    std::cout << a1;

    return 0;
}
