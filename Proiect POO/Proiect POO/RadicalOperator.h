// RadicalOperator.h
#ifndef RADICAL_OPERATOR_H
#define RADICAL_OPERATOR_H

#include "Operator.h"

class RadicalOperator : public Operator {
public:
    double evaluate(double operand1, double operand2) const override;
    int getPriority() const override;

    RadicalOperator operator[](const RadicalOperator& other) const;
    friend ostream& operator<<(ostream& os, const RadicalOperator& radOp);
    bool operator>(const RadicalOperator& other) const;
};

#endif // RADICAL_OPERATOR_H
