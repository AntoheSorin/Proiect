// Operator.h
#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>

class Operator {
public:
    virtual double evaluate(double operand1, double operand2) const = 0;
    virtual int getPriority() const = 0;
};

#endif // OPERATOR_H
