# Customer Support Ticket System

This project implements a comprehensive Customer Support Ticket System using various data structures including singly linked lists, stacks, priority queues, circular queues, and polynomial linked lists.

## Overview

The Customer Support Ticket System manages customer support tickets with the following features:
- Add, delete, and retrieve tickets
- Undo functionality for ticket operations
- Priority-based ticket processing for urgent issues
- Round-robin ticket processing for fair handling
- Billing history comparison using polynomial linked lists

## Data Structures Used

1. **Singly Linked List**: Stores all active tickets dynamically
2. **Stack**: Implements undo functionality for ticket operations
3. **Priority Queue**: Ensures urgent tickets are processed first
4. **Circular Queue**: Manages round-robin ticket processing
5. **Polynomial Linked List**: Represents and compares customer billing records

## Time & Space Complexity

| Operation | Data Structure | Time Complexity | Space Complexity |
|-----------|----------------|----------------|-----------------|
| insertTicket() | Singly Linked List | O(1) (at tail) | O(1) |
| deleteTicket() | Singly Linked List | O(n) | O(1) |
| retrieveTicket() | Singly Linked List | O(n) | O(1) |
| undoTicketOperation() | Stack | O(1) | O(n) |
| processPriorityTickets() | Priority Queue | O(log n) | O(n) |
| processRoundRobinTickets() | Circular Queue | O(n) | O(n) |
| compareBillingHistory() | Polynomial Linked List | O(m + n) | O(max(m, n)) |

## Project Structure

```
📦 Lab_Assignment_2_Customer_Support_Ticket_System/
│
├── 📁 src/
│   ├── main.cpp                   # Complete implementation
│   ├── TicketADT.h                # Ticket class header
│   ├── LinkedList.h               # Singly linked list for tickets
│   ├── Stack.h                    # Undo stack
│   ├── Queue.h                    # Circular and priority queues
│   ├── PolynomialLinkedList.h     # Billing record comparison
│
├── 📁 reports/
│   ├── Implementation_Report.md   # Full explanation of design
│   ├── Complexity_Analysis.md     # Table of time & space complexities
│
├── 📁 screenshots/
│   ├── output_add_ticket.png
│   ├── output_priority.png
│   ├── output_round_robin.png
│   ├── output_undo.png
│
└── README.md                      # This file
```

## Compilation and Execution

To compile and run the program:

```bash
g++ -o ticket_system src/main.cpp
./ticket_system
```

## System Behavior

When the program runs, it displays a menu-driven interface:

```
========== CUSTOMER SUPPORT TICKET SYSTEM ==========
1. Add New Ticket
2. Delete Ticket by ID
3. Undo Last Operation
4. Process Urgent Tickets (Priority Queue)
5. Round-Robin Ticket Processing
6. Compare Billing History (Polynomial Linked Lists)
7. Display All Active Tickets
8. Exit
====================================================
```

## Learning Outcomes

This project demonstrates understanding of:
- Implementation of singly linked lists, stacks, queues in practical applications
- The role of priority and circular queues in scheduling and workflow systems
- Application of polynomial linked lists for record comparison
- Analysis of time and space complexity for each operation