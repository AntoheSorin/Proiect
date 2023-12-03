// main.cpp
#include <iostream>
#include "Calculator.h"
#include "AddOperator.h"
#include "SubtractOperator.h"
#include "MultiplyOperator.h"
#include "DivideOperator.h"
#include "PowerOperator.h"
#include "RadicalOperator.h"

using namespace std;

int main() {
    Calculator calculator;

    const char* expression;
    while (true) {
        cout << "Enter an expression (type 'exit' to quit): ";
        cin.getline(Calculator::expressionBuffer, Calculator::MAX_EXPRESSION_LENGTH);
        expression = Calculator::expressionBuffer;

        if (strcmp(expression, "exit") == 0) {
            break;
        }

        try {
            calculator.setExpression(expression);
            double result = calculator.evaluateExpression(calculator.getExpression());
            cout << "Result: " << result << endl;

            
            AddOperator add1, add2;
            SubtractOperator sub1, sub2;
            MultiplyOperator mul1, mul2;
            DivideOperator div1, div2;
            PowerOperator pow1, pow2;
            RadicalOperator rad1, rad2;

            
            AddOperator addResult = add1 + add2;
            SubtractOperator subResult = sub1 - sub2;
            MultiplyOperator mulResult = mul1 * mul2;
            DivideOperator divResult = div1 / div2;
            PowerOperator powResult = pow1 ^ pow2;
            RadicalOperator radResult = rad1[rad2];

            
            cout << "Addition Result: " << addResult << endl;
            cout << "Subtraction Result: " << subResult << endl;
            cout << "Multiplication Result: " << mulResult << endl;
            cout << "Division Result: " << divResult << endl;
            cout << "Power Result: " << powResult << endl;
            cout << "Radical Result: " << radResult << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
