# Implementation Report: Customer Support Ticket System

## Introduction
This report provides a detailed explanation of the Customer Support Ticket System implementation. The system is designed to manage customer support tickets efficiently using various data structures including linked lists, stacks, queues, and polynomial linked lists.

## Ticket ADT Description
The Ticket ADT represents a customer support ticket with the following attributes:
- **TicketID**: Unique identifier for each ticket
- **CustomerName**: Name of the customer
- **IssueDescription**: Description of the customer's issue
- **Priority**: Ticket priority level (1 = urgent, 2 = normal, etc.)

## System Design
The system utilizes the following data structures:

### 1. Singly Linked List
- **Purpose**: Stores all active tickets dynamically
- **Implementation**: Each node contains a Ticket object and a pointer to the next node
- **Operations**: insertTicket(), deleteTicket(), retrieveTicket()

### 2. Stack
- **Purpose**: Stores recent operations for undo functionality
- **Implementation**: Vector-based stack storing Operation objects (ADD or DELETE)
- **Operations**: push(), pop()

### 3. Priority Queue
- **Purpose**: Ensures urgent tickets are processed first
- **Implementation**: Heap-based priority queue with priority determined by ticket priority value
- **Operations**: enqueue(), dequeue()

### 4. Circular Queue
- **Purpose**: Manages round-robin ticket processing
- **Implementation**: Array-based circular queue with front and rear pointers
- **Operations**: enqueue(), dequeue()

### 5. Polynomial Linked List
- **Purpose**: Represents and compares customer billing records
- **Implementation**: Linked list where each node represents a term in a polynomial
- **Operations**: addTerm(), compare()

## Implementation Steps

1. **Define the Ticket ADT**: Created a Ticket class with necessary attributes and methods
2. **Implement Linked List**: Developed a singly linked list to store and manage tickets
3. **Implement Stack**: Created a stack to track operations for undo functionality
4. **Implement Queues**: Developed priority queue for urgent tickets and circular queue for round-robin processing
5. **Implement Polynomial Linked List**: Created a specialized linked list for billing history comparison
6. **Build Menu-Driven System**: Integrated all components into a user-friendly interface

## Sample Implementation Details

### Ticket Insertion
```cpp
void insertTicket(const Ticket& ticket) {
    Node* newNode = new Node(ticket);
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}
```

### Undo Functionality
```cpp
void undoLastOperation() {
    Operation lastOp(ADD, Ticket(0, "", "", 0));
    
    if (undoStack.pop(lastOp)) {
        if (lastOp.type == ADD) {
            ticketList.deleteTicket(lastOp.ticket.getTicketID());
        } else if (lastOp.type == DELETE) {
            ticketList.insertTicket(lastOp.ticket);
        }
    }
}
```

## Conclusion
The Customer Support Ticket System demonstrates the practical application of various data structures in a real-world scenario. The system efficiently manages customer support tickets with features like undo functionality, priority-based processing, and round-robin scheduling. The implementation showcases the importance of choosing appropriate data structures for specific operations to optimize time and space complexity.