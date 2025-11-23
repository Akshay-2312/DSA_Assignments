#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

// Node structure for Expression Tree
struct ExpressionNode {
     string value;
    ExpressionNode* left;
    ExpressionNode* right;
    
    ExpressionNode( string val) : value(val), left(nullptr), right(nullptr) {}
};

// Expression Tree class
class ExpressionTree {
private:
    ExpressionNode* root;
    
    // Helper function to check if a character is an operator
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }
    
    // Helper function to get precedence of an operator
    int getPrecedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        if (op == '^')
            return 3;
        return 0;
    }
    
    // Convert infix expression to postfix
     string infixToPostfix(const  string& infix) {
         stack<char> s;
         string postfix;
        
        for (size_t i = 0; i < infix.length(); i++) {
            char c = infix[i];
            
            // If the character is an operand, add it to the postfix expression
            if (isalnum(c)) {
                // Handle multi-digit numbers
                 string number;
                while (i < infix.length() && (isalnum(infix[i]) || infix[i] == '.')) {
                    number += infix[i];
                    i++;
                }
                i--; // Adjust for the loop increment
                postfix += number + " ";
            }
            // If the character is an opening bracket, push it to the stack
            else if (c == '(') {
                s.push(c);
            }
            // If the character is a closing bracket, pop and add to postfix until an opening bracket is found
            else if (c == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    postfix += " ";
                    s.pop();
                }
                if (!s.empty() && s.top() == '(') {
                    s.pop(); // Remove the opening bracket
                }
            }
            // If the character is an operator
            else if (isOperator(c)) {
                while (!s.empty() && s.top() != '(' && getPrecedence(s.top()) >= getPrecedence(c)) {
                    postfix += s.top();
                    postfix += " ";
                    s.pop();
                }
                s.push(c);
            }
        }
        
        // Pop all remaining operators from the stack
        while (!s.empty()) {
            if (s.top() != '(') {
                postfix += s.top();
                postfix += " ";
            }
            s.pop();
        }
        
        return postfix;
    }
    
    // Build expression tree from postfix expression
    ExpressionNode* buildTree(const  string& postfix) {
         stack<ExpressionNode*> st;
        
        // Process each token in the postfix expression
         string token;
        for (size_t i = 0; i < postfix.length(); i++) {
            char c = postfix[i];
            
            // Skip spaces
            if (c == ' ') {
                if (!token.empty()) {
                    // If token is an operand, create a node and push to stack
                    if (!isOperator(token[0]) || (token.length() > 1 && token[0] == '-')) {
                        st.push(new ExpressionNode(token));
                    }
                    // If token is an operator, pop two nodes, create a new node, and push it back
                    else {
                        ExpressionNode* node = new ExpressionNode(token);
                        
                        // Pop right and left operands
                        if (!st.empty()) {
                            node->right = st.top();
                            st.pop();
                        }
                        
                        if (!st.empty()) {
                            node->left = st.top();
                            st.pop();
                        }
                        
                        // Push the new node back to the stack
                        st.push(node);
                    }
                    token.clear();
                }
                continue;
            }
            
            token += c;
        }
        
        // Process the last token if any
        if (!token.empty()) {
            if (!isOperator(token[0]) || (token.length() > 1 && token[0] == '-')) {
                st.push(new ExpressionNode(token));
            } else {
                ExpressionNode* node = new ExpressionNode(token);
                
                if (!st.empty()) {
                    node->right = st.top();
                    st.pop();
                }
                
                if (!st.empty()) {
                    node->left = st.top();
                    st.pop();
                }
                
                st.push(node);
            }
        }
        
        // The final node in the stack is the root of the expression tree
        return st.empty() ? nullptr : st.top();
    }
    
    // Evaluate expression tree recursively
    double evaluate(ExpressionNode* node) {
        if (!node) return 0;
        
        // If node is a leaf (operand)
        if (!node->left && !node->right) {
            return  stod(node->value);
        }
        
        // Evaluate left and right subtrees
        double leftVal = evaluate(node->left);
        double rightVal = evaluate(node->right);
        
        // Apply operator
        if (node->value == "+") return leftVal + rightVal;
        if (node->value == "-") return leftVal - rightVal;
        if (node->value == "*") return leftVal * rightVal;
        if (node->value == "/") return leftVal / rightVal;
        if (node->value == "^") return pow(leftVal, rightVal);
        
        return 0;
    }
    
    // Clean up memory
    void destroyTree(ExpressionNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    // Print expression tree (inorder traversal)
    void printInorder(ExpressionNode* node) {
        if (node) {
            if (node->left || node->right)  cout << "(";
            
            printInorder(node->left);
             cout << node->value;
            printInorder(node->right);
            
            if (node->left || node->right)  cout << ")";
        }
    }
    
public:
    ExpressionTree() : root(nullptr) {}
    
    ~ExpressionTree() {
        destroyTree(root);
    }
    
    // Build and evaluate expression
    double evaluateExpression(const  string& infix) {
        // Convert infix to postfix
         string postfix = infixToPostfix(infix);
        
        // Clean up previous tree if any
        destroyTree(root);
        
        // Build expression tree
        root = buildTree(postfix);
        
        // Evaluate expression tree
        return evaluate(root);
    }
    
    // Print the expression tree
    void printExpression() {
         cout << "Expression Tree (Inorder): ";
        printInorder(root);
         cout <<  endl;
    }
};

#endif // EXPRESSION_TREE_H