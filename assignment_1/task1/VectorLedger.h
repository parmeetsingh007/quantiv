#ifndef VECTOR_LEDGER_H
#define VECTOR_LEDGER_H

#include <vector>
#include "AbstractLedger.h"

class VectorLedger : public AbstractLedger {
private:
    std::vector<Transaction> data;

public:
    VectorLedger() = default;
    VectorLedger(const VectorLedger &other);
    AbstractLedger& operator+=(const Transaction&) override;
    AbstractLedger& operator-=(int) override;
    bool operator==(const AbstractLedger&) const override;
    AbstractLedger* operator+(const AbstractLedger&) const override;
    AbstractLedger& operator=(const AbstractLedger&) override;
    void print(std::ostream&) const override;
};

#endif
