#ifndef ARRAY_LEDGER_H
#define ARRAY_LEDGER_H

#include "AbstractLedger.h"

class ArrayLedger : public AbstractLedger {
private:
    static const int MAX_SIZE = 100;
    Transaction data[MAX_SIZE];
    int size;

public:
    ArrayLedger();
    ArrayLedger(const ArrayLedger &other);
    AbstractLedger& operator+=(const Transaction&) override;
    AbstractLedger& operator-=(int) override;
    bool operator==(const AbstractLedger&) const override;
    AbstractLedger* operator+(const AbstractLedger&) const override;
    AbstractLedger& operator=(const AbstractLedger&) override;
    void print(std::ostream&) const override;
};

#endif
