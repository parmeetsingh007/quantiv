#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include "Gate.h"
#include "Input.h"

class Circuit {
private:
    std::vector<const Gate*> gates;

public:
    void addGate(const Gate* g);
    int getGateCount() const;
    Input Evaluate(const std::vector<const Input*>& inputs) const;
};

#endif
