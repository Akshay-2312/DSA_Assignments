#ifndef STACK_H
#define STACK_H

#include "TicketADT.h"
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

// Operation type for undo functionality
enum OperationType {
    ADD,
    DELETE
};

// Structure to store operations for undo functionality
struct Operation {
    OperationType type;
    Ticket ticket;
    
    // Constructor
    Operation(OperationType t, const Ticket& tkt) : type(t), ticket(tkt) {}
};

// Stack implementation for undo functionality
class Stack {
private:
     vector<Operation> operations;

public:
    // Push an operation onto the stack
    // Time Complexity: O(1)
    void push(const Operation& op) {
        operations.push_back(op);
    }
    
    // Pop an operation from the stack
    // Time Complexity: O(1)
    bool pop(Operation& op) {
        if (operations.empty()) {
            return false;
        }
        
        op = operations.back();
        operations.pop_back();
        return true;
    }
    
    // Check if the stack is empty
    bool isEmpty() const {
        return operations.empty();
    }
    
    // Get the size of the stack
    size_t size() const {
        return operations.size();
    }
};

#endif // STACK_H