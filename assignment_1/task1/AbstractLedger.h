#ifndef ABSTRACT_LEDGER_H
#define ABSTRACT_LEDGER_H

#include <iostream>
#include "Transaction.h"

class AbstractLedger {
public:
    virtual ~AbstractLedger() {}
    virtual AbstractLedger& operator+=(const Transaction&) = 0;
    virtual AbstractLedger& operator-=(int) = 0;
    virtual bool operator==(const AbstractLedger&) const = 0;
    virtual bool operator!=(const AbstractLedger& other) const { return !(*this == other); }
    virtual AbstractLedger* operator+(const AbstractLedger&) const = 0;
    virtual AbstractLedger& operator=(const AbstractLedger&) = 0;
    virtual void print(std::ostream&) const = 0;
};

inline std::ostream& operator<<(std::ostream &os, const AbstractLedger &l) {
    l.print(os);
    return os;
}

#endif
