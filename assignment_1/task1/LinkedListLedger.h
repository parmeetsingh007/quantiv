#ifndef LINKED_LIST_LEDGER_H
#define LINKED_LIST_LEDGER_H

#include "AbstractLedger.h"

class LinkedListLedger : public AbstractLedger {
private:
    struct Node {
        Transaction tx;
        Node *next;
        Node(const Transaction &t) : tx(t), next(nullptr) {}
    };
    Node *head;
    Node *tail;
    int size;
    void clear();
    void copyFrom(const LinkedListLedger &other);

public:
    LinkedListLedger();
    LinkedListLedger(const LinkedListLedger &other);
    ~LinkedListLedger();
    AbstractLedger& operator+=(const Transaction&) override;
    AbstractLedger& operator-=(int) override;
    bool operator==(const AbstractLedger&) const override;
    AbstractLedger* operator+(const AbstractLedger&) const override;
    AbstractLedger& operator=(const AbstractLedger&) override;
    void print(std::ostream&) const override;
};

#endif
