// DivideOperator.h
#ifndef DIVIDE_OPERATOR_H
#define DIVIDE_OPERATOR_H

#include "Operator.h"

class DivideOperator : public Operator {
public:
    double evaluate(double operand1, double operand2) const override;
    int getPriority() const override;

    DivideOperator operator/(const DivideOperator& other) const;
    friend ostream& operator<<(ostream& os, const DivideOperator& divOp);
    bool operator!=(const DivideOperator& other) const;
};

#endif // DIVIDE_OPERATOR_H
