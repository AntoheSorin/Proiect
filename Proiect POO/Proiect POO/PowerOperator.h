// PowerOperator.h
#ifndef POWER_OPERATOR_H
#define POWER_OPERATOR_H

#include "Operator.h"

class PowerOperator : public Operator {
public:
    double evaluate(double operand1, double operand2) const override;
    int getPriority() const override;

    PowerOperator operator^(const PowerOperator& other) const;
    friend ostream& operator<<(ostream& os, const PowerOperator& powOp);
    bool operator<=(const PowerOperator& other) const;
};

#endif // POWER_OPERATOR_H
