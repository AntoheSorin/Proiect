// MultiplyOperator.h
#ifndef MULTIPLY_OPERATOR_H
#define MULTIPLY_OPERATOR_H

#include "Operator.h"

class MultiplyOperator : public Operator {
public:
    double evaluate(double operand1, double operand2) const override;
    int getPriority() const override;

    MultiplyOperator operator*(const MultiplyOperator& other) const;
    friend ostream& operator<<(ostream& os, const MultiplyOperator& mulOp);
    bool operator>=(const MultiplyOperator& other) const;
};

#endif // MULTIPLY_OPERATOR_H
