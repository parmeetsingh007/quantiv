#include <iostream>
#include <vector>
#include "Circuit.h"
#include "Gate.h"
#include "Input.h"

int main() {
    AndGate andGate;
    OrGate orGate;
    XorGate xorGate;
    NandGate nandGate;
    NorGate norGate;
    XnorGate xnorGate;

    const Input& T = Input::T();
    const Input& F = Input::F();

    Circuit c1;
    c1.addGate(&andGate);
    c1.addGate(&orGate);
    c1.addGate(&xorGate);

    std::vector<const Input*> inputs1 = { &T, &T, &F, &T };
    Input r1 = c1.Evaluate(inputs1);
    std::cout << "Test 1 (((T AND T) OR F) XOR T) = " << r1.getValue() << "\n";

    Circuit c2;
    c2.addGate(&nandGate);
    c2.addGate(&norGate);
    c2.addGate(&xnorGate);

    std::vector<const Input*> inputs2 = { &T, &F, &T, &T };
    Input r2 = c2.Evaluate(inputs2);
    std::cout << "Test 2 (T NAND F, NOR T, XNOR T) = " << r2.getValue() << "\n";

    Circuit c3;
    c3.addGate(&orGate);
    std::vector<const Input*> inputs3 = { &F, &T };
    Input r3 = c3.Evaluate(inputs3);
    std::cout << "Test 3 (F OR T) = " << r3.getValue() << "\n";

    return 0;
}
