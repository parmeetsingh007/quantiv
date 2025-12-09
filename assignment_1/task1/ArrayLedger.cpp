#include "ArrayLedger.h"

ArrayLedger::ArrayLedger() : size(0) {}

ArrayLedger::ArrayLedger(const ArrayLedger &other) : size(other.size) {
    for (int i = 0; i < size; i++) data[i] = other.data[i];
}

AbstractLedger& ArrayLedger::operator+=(const Transaction &t) {
    if (size < MAX_SIZE) data[size++] = t;
    return *this;
}

AbstractLedger& ArrayLedger::operator-=(int) {
    if (size > 0) size--;
    return *this;
}

bool ArrayLedger::operator==(const AbstractLedger &other) const {
    const ArrayLedger *o = dynamic_cast<const ArrayLedger*>(&other);
    if (!o || size != o->size) return false;
    for (int i = 0; i < size; i++) {
        if (data[i].type != o->data[i].type ||
            data[i].ticker != o->data[i].ticker ||
            data[i].quantity != o->data[i].quantity)
            return false;
    }
    return true;
}

AbstractLedger* ArrayLedger::operator+(const AbstractLedger &other) const {
    const ArrayLedger *o = dynamic_cast<const ArrayLedger*>(&other);
    ArrayLedger *res = new ArrayLedger(*this);
    if (o) {
        for (int i = 0; i < o->size; i++) (*res) += o->data[i];
    }
    return res;
}

AbstractLedger& ArrayLedger::operator=(const AbstractLedger &other) {
    const ArrayLedger *o = dynamic_cast<const ArrayLedger*>(&other);
    if (o) {
        size = o->size;
        for (int i = 0; i < size; i++) data[i] = o->data[i];
    }
    return *this;
}

void ArrayLedger::print(std::ostream &os) const {
    for (int i = 0; i < size; i++)
        os << data[i].type << " " << data[i].ticker << " " << data[i].quantity << "\n";
}
