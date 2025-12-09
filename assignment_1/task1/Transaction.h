#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction {
    std::string type;
    std::string ticker;
    int quantity;

    Transaction() : quantity(0) {}
    Transaction(const std::string &t, const std::string &tk, int q)
        : type(t), ticker(tk), quantity(q) {}

    bool operator==(const Transaction &other) const {
        return type == other.type &&
               ticker == other.ticker &&
               quantity == other.quantity;
    }
};

#endif
