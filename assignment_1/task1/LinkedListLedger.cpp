#include "LinkedListLedger.h"

LinkedListLedger::LinkedListLedger() : head(nullptr), tail(nullptr), size(0) {}

LinkedListLedger::LinkedListLedger(const LinkedListLedger &other) : head(nullptr), tail(nullptr), size(0) {
    copyFrom(other);
}

LinkedListLedger::~LinkedListLedger() {
    clear();
}

void LinkedListLedger::clear() {
    Node *cur = head;
    while (cur) {
        Node *next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    size = 0;
}

void LinkedListLedger::copyFrom(const LinkedListLedger &other) {
    Node *cur = other.head;
    while (cur) {
        (*this) += cur->tx;
        cur = cur->next;
    }
}

AbstractLedger& LinkedListLedger::operator+=(const Transaction &t) {
    Node *node = new Node(t);
    if (!head) head = tail = node;
    else {
        tail->next = node;
        tail = node;
    }
    size++;
    return *this;
}

AbstractLedger& LinkedListLedger::operator-=(int) {
    if (!head) return *this;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        size = 0;
        return *this;
    }
    Node *cur = head;
    while (cur->next != tail) cur = cur->next;
    delete tail;
    tail = cur;
    tail->next = nullptr;
    size--;
    return *this;
}

bool LinkedListLedger::operator==(const AbstractLedger &other) const {
    const LinkedListLedger *o = dynamic_cast<const LinkedListLedger*>(&other);
    if (!o || size != o->size) return false;
    Node *a = head;
    Node *b = o->head;
    while (a && b) {
        if (a->tx.type != b->tx.type || a->tx.ticker != b->tx.ticker || a->tx.quantity != b->tx.quantity)
            return false;
        a = a->next;
        b = b->next;
    }
    return true;
}

AbstractLedger* LinkedListLedger::operator+(const AbstractLedger &other) const {
    const LinkedListLedger *o = dynamic_cast<const LinkedListLedger*>(&other);
    LinkedListLedger *res = new LinkedListLedger(*this);
    if (o) {
        Node *cur = o->head;
        while (cur) {
            (*res) += cur->tx;
            cur = cur->next;
        }
    }
    return res;
}

AbstractLedger& LinkedListLedger::operator=(const AbstractLedger &other) {
    const LinkedListLedger *o = dynamic_cast<const LinkedListLedger*>(&other);
    if (o) {
        clear();
        copyFrom(*o);
    }
    return *this;
}

void LinkedListLedger::print(std::ostream &os) const {
    Node *cur = head;
    while (cur) {
        os << cur->tx.type << " " << cur->tx.ticker << " " << cur->tx.quantity << "\n";
        cur = cur->next;
    }
}
