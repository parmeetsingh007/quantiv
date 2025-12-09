#include "Gate.h"

Input AndGate::Evaluate(const Input& a, const Input& b) const {
    return Input::fromInt(a.getValue() && b.getValue());
}

Input OrGate::Evaluate(const Input& a, const Input& b) const {
    return Input::fromInt(a.getValue() || b.getValue());
}

Input XorGate::Evaluate(const Input& a, const Input& b) const {
    return Input::fromInt(a.getValue() ^ b.getValue());
}

Input NandGate::Evaluate(const Input& a, const Input& b) const {
    return Input::fromInt(!(a.getValue() && b.getValue()));
}

Input NorGate::Evaluate(const Input& a, const Input& b) const {
    return Input::fromInt(!(a.getValue() || b.getValue()));
}

Input XnorGate::Evaluate(const Input& a, const Input& b) const {
    return Input::fromInt(!(a.getValue() ^ b.getValue()));
}
