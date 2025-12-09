#ifndef INPUT_H
#define INPUT_H

struct Input {
private:
    int value;
    explicit Input(int v) : value(v) {}

public:
    static const Input& T() {
        static Input instance(1);
        return instance;
    }

    static const Input& F() {
        static Input instance(0);
        return instance;
    }

    int getValue() const {
        return value;
    }

    static Input fromInt(int v) {
        return Input(v ? 1 : 0);
    }
};

#endif
