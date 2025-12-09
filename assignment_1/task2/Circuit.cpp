#include "Circuit.h"

void Circuit::addGate(const Gate* g) {
    gates.push_back(g);
}

int Circuit::getGateCount() const {
    return (int)gates.size();
}

Input Circuit::Evaluate(const std::vector<const Input*>& inputs) const {
    if (gates.empty() || inputs.size() < 2) return Input::fromInt(0);
    Input result = gates[0]->Evaluate(*inputs[0], *inputs[1]);
    for (std::size_t i = 1; i < gates.size() && i + 1 < inputs.size(); ++i) {
        result = gates[i]->Evaluate(result, *inputs[i + 1]);
    }
    return result;
}
