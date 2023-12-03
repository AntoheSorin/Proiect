// Calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Operator.h"

class Calculator {
public:
    double evaluateExpression(const char* expression);

    const char* getExpression() const;
    void setExpression(const char* expression);

private:
    double applyOperator(const Operator& op, double operand1, double operand2);

    static const int MAX_EXPRESSION_LENGTH = 100;
    static char expressionBuffer[MAX_EXPRESSION_LENGTH];

    static double numericValues[MAX_EXPRESSION_LENGTH];
};

#endif // CALCULATOR_H
