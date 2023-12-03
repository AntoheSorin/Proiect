// AddOperator.h
#ifndef ADD_OPERATOR_H
#define ADD_OPERATOR_H

#include "Operator.h"

class AddOperator : public Operator {
public:
    double evaluate(double operand1, double operand2) const override;
    int getPriority() const override;

    AddOperator operator+(const AddOperator& other) const;
    friend ostream& operator<<(ostream& os, const AddOperator& addOp);
    bool operator==(const AddOperator& other) const;
};

#endif // ADD_OPERATOR_H
