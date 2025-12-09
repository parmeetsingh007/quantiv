#ifndef GATE_H
#define GATE_H

#include "Input.h"

class Gate {
public:
    virtual ~Gate() {}
    virtual Input Evaluate(const Input& a, const Input& b) const = 0;
};

class AndGate : public Gate {
public:
    Input Evaluate(const Input& a, const Input& b) const override;
};

class OrGate : public Gate {
public:
    Input Evaluate(const Input& a, const Input& b) const override;
};

class XorGate : public Gate {
public:
    Input Evaluate(const Input& a, const Input& b) const override;
};

class NandGate : public Gate {
public:
    Input Evaluate(const Input& a, const Input& b) const override;
};

class NorGate : public Gate {
public:
    Input Evaluate(const Input& a, const Input& b) const override;
};

class XnorGate : public Gate {
public:
    Input Evaluate(const Input& a, const Input& b) const override;
};

#endif
