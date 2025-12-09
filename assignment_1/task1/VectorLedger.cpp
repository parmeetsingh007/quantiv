#include "VectorLedger.h"

VectorLedger::VectorLedger(const VectorLedger &other) {
    data = other.data;
}

AbstractLedger& VectorLedger::operator+=(const Transaction &t) {
    data.push_back(t);
    return *this;
}

AbstractLedger& VectorLedger::operator-=(int) {
    if (!data.empty()) data.pop_back();
    return *this;
}

bool VectorLedger::operator==(const AbstractLedger &other) const {
    const VectorLedger *o = dynamic_cast<const VectorLedger*>(&other);
    return o && data == o->data;
}

AbstractLedger* VectorLedger::operator+(const AbstractLedger &other) const {
    const VectorLedger *o = dynamic_cast<const VectorLedger*>(&other);
    VectorLedger *res = new VectorLedger(*this);
    if (o) res->data.insert(res->data.end(), o->data.begin(), o->data.end());
    return res;
}

AbstractLedger& VectorLedger::operator=(const AbstractLedger &other) {
    const VectorLedger *o = dynamic_cast<const VectorLedger*>(&other);
    if (o) data = o->data;
    return *this;
}

void VectorLedger::print(std::ostream &os) const {
    for (const auto &t : data) os << t.type << " " << t.ticker << " " << t.quantity << "\n";
}
