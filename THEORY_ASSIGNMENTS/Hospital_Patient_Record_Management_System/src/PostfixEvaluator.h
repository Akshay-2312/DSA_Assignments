#ifndef POSTFIX_EVALUATOR_H
#define POSTFIX_EVALUATOR_H

#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <stdexcept>
using namespace std;

class PostfixEvaluator {
public:
    static double evaluate(const string& expr) {
        istringstream iss(expr);
        stack<double> st;
        string tok;
        while (iss >> tok) {
            if (isNumber(tok)) {
                st.push(stod(tok));
            } else {
                if (st.size() < 2) throw runtime_error("Invalid postfix expression");
                double b = st.top(); st.pop();
                double a = st.top(); st.pop();
                st.push(applyOp(a, b, tok));
            }
        }
        if (st.size() != 1) throw runtime_error("Invalid postfix expression");
        return st.top();
    }

private:
    static bool isNumber(const string& s) {
        char* end = nullptr;
        strtod(s.c_str(), &end);
        return end && *end == '\0';
    }

    static double applyOp(double a, double b, const string& op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") return b == 0.0 ? throw runtime_error("Division by zero") : a / b;
        if (op == "^") return pow(a, b);
        throw runtime_error("Unsupported operator: " + op);
    }
};

#endif