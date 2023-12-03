// SubtractOperator.h
#ifndef SUBTRACT_OPERATOR_H
#define SUBTRACT_OPERATOR_H

#include "Operator.h"

class SubtractOperator : public Operator {
public:
    double evaluate(double operand1, double operand2) const override;
    int getPriority() const override;

    SubtractOperator operator-(const SubtractOperator& other) const;
    friend ostream& operator<<(ostream& os, const SubtractOperator& subOp);
    bool operator<(const SubtractOperator& other) const;
};

#endif // SUBTRACT_OPERATOR_H
