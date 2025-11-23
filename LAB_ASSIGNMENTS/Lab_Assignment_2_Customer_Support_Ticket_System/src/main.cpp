#include <iostream>
#include <string>
#include <limits>
#include "TicketADT.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "PolynomialLinkedList.h"
using namespace std;

// Global variables
LinkedList ticketList;
Stack undoStack;
PriorityQueue priorityQueue;
CircularQueue circularQueue(10);
int nextTicketID = 1001; // Starting ticket ID

// Function prototypes
void displayMenu();
void addNewTicket();
void deleteTicket();
void undoLastOperation();
void processUrgentTickets();
void processRoundRobinTickets();
void compareBillingHistory();
void displayAllTickets();

int main() {
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            // Input validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        
        switch (choice) {
            case 1:
                addNewTicket();
                break;
            case 2:
                deleteTicket();
                break;
            case 3:
                undoLastOperation();
                break;
            case 4:
                processUrgentTickets();
                break;
            case 5:
                processRoundRobinTickets();
                break;
            case 6:
                compareBillingHistory();
                break;
            case 7:
                displayAllTickets();
                break;
            case 8:
             cout << "Exiting the system. Thank you!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}

// Display the menu
void displayMenu() {
     cout << "\n========== CUSTOMER SUPPORT TICKET SYSTEM ==========\n";
     cout << "1. Add New Ticket\n";
     cout << "2. Delete Ticket by ID\n";
     cout << "3. Undo Last Operation\n";
     cout << "4. Process Urgent Tickets (Priority Queue)\n";
     cout << "5. Round-Robin Ticket Processing\n";
     cout << "6. Compare Billing History (Polynomial Linked Lists)\n";
     cout << "7. Display All Active Tickets\n";
     cout << "8. Exit\n";
     cout << "====================================================\n";
}

// Add a new ticket
void addNewTicket() {
    string customerName, issueDescription;
    int priority;
    
    cout << "\n----- Add New Ticket -----\n";
    
    cout << "Enter customer name: ";
    getline(cin, customerName);
    
    cout << "Enter issue description: ";
    getline(cin, issueDescription);
    
    cout << "Enter priority (1 = urgent, 2 = normal, etc.): ";
    while (!(cin >> priority) || priority < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid priority. Please enter a positive number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Create a new ticket
    Ticket newTicket(nextTicketID, customerName, issueDescription, priority);
    
    // Add to the linked list
    ticketList.insertTicket(newTicket);
    
    // Add to the priority queue if urgent
    if (priority == 1) {
        priorityQueue.enqueue(newTicket);
    }
    
    // Add to the circular queue for round-robin processing
    circularQueue.enqueue(newTicket);
    
    // Add to the undo stack
    undoStack.push(Operation(ADD, newTicket));
    
     cout << "Ticket added successfully with ID: " << nextTicketID <<  endl;
    nextTicketID++;
}

// Delete a ticket by ID
void deleteTicket() {
    int ticketID;
    
     cout << "\n----- Delete Ticket -----\n";
     cout << "Enter ticket ID to delete: ";
    
    while (!( cin >> ticketID)) {
         cin.clear();
         cin.ignore( numeric_limits< streamsize>::max(), '\n');
         cout << "Invalid ID. Please enter a number: ";
    }
     cin.ignore( numeric_limits< streamsize>::max(), '\n');
    
    // Find the ticket first to store it for undo
    Ticket* ticket = ticketList.retrieveTicket(ticketID);
    
    if (ticket != nullptr) {
        // Store the ticket for undo
        undoStack.push(Operation(DELETE, *ticket));
        
        // Delete from the linked list
        if (ticketList.deleteTicket(ticketID)) {
             cout << "Ticket with ID " << ticketID << " deleted successfully.\n";
        } else {
             cout << "Failed to delete ticket.\n";
        }
    } else {
         cout << "Ticket with ID " << ticketID << " not found.\n";
    }
}

// Undo the last operation
void undoLastOperation() {
    Operation lastOp(ADD, Ticket(0, "", "", 0)); // Dummy operation
    
     cout << "\n----- Undo Last Operation -----\n";
    
    if (undoStack.pop(lastOp)) {
        if (lastOp.type == ADD) {
            // If the last operation was ADD, we need to delete the ticket
            if (ticketList.deleteTicket(lastOp.ticket.getTicketID())) {
                 cout << "Undid addition of ticket with ID " << lastOp.ticket.getTicketID() <<  endl;
            } else {
                 cout << "Failed to undo addition operation.\n";
            }
        } else if (lastOp.type == DELETE) {
            // If the last operation was DELETE, we need to add the ticket back
            ticketList.insertTicket(lastOp.ticket);
            
            // Add back to priority queue if urgent
            if (lastOp.ticket.getPriority() == 1) {
                priorityQueue.enqueue(lastOp.ticket);
            }
            
            // Add back to circular queue
            circularQueue.enqueue(lastOp.ticket);
            
             cout << "Undid deletion of ticket with ID " << lastOp.ticket.getTicketID() <<  endl;
        }
    } else {
         cout << "No operations to undo.\n";
    }
}

// Process urgent tickets using priority queue
void processUrgentTickets() {
     cout << "\n----- Process Urgent Tickets -----\n";
    
    if (priorityQueue.isEmpty()) {
         cout << "No urgent tickets to process.\n";
        return;
    }
    
    priorityQueue.display();
    
     cout << "Processing the highest priority ticket...\n";
    Ticket ticket(0, "", "", 0);
    
    if (priorityQueue.dequeue(ticket)) {
         cout << "Processed ticket with ID " << ticket.getTicketID() <<  endl;
         cout << "Customer: " << ticket.getCustomerName() <<  endl;
         cout << "Issue: " << ticket.getIssueDescription() <<  endl;
         cout << "Priority: " << ticket.getPriority() <<  endl;
    } else {
         cout << "Failed to process ticket.\n";
    }
}

// Process tickets in round-robin fashion
void processRoundRobinTickets() {
     cout << "\n----- Round-Robin Ticket Processing -----\n";
    
    if (circularQueue.isEmpty()) {
         cout << "No tickets in the round-robin queue.\n";
        return;
    }
    
    circularQueue.display();
    
     cout << "Processing the next ticket in round-robin order...\n";
    Ticket ticket(0, "", "", 0);
    
    if (circularQueue.dequeue(ticket)) {
         cout << "Processed ticket with ID " << ticket.getTicketID() <<  endl;
         cout << "Customer: " << ticket.getCustomerName() <<  endl;
         cout << "Issue: " << ticket.getIssueDescription() <<  endl;
         cout << "Priority: " << ticket.getPriority() <<  endl;
        
        // Re-enqueue the ticket for continuous processing
         cout << "Re-enqueueing the ticket for future processing...\n";
        circularQueue.enqueue(ticket);
    } else {
         cout << "Failed to process ticket.\n";
    }
}

// Compare billing history using polynomial linked lists
void compareBillingHistory() {
     cout << "\n----- Compare Billing History -----\n";
    
     string customer1, customer2;
    
     cout << "Enter first customer name: ";
     getline( cin, customer1);
    
     cout << "Enter second customer name: ";
     getline( cin, customer2);
    
    // Create polynomial linked lists for each customer
    PolynomialLinkedList poly1(customer1);
    PolynomialLinkedList poly2(customer2);
    
    // Add some sample billing data
    // For customer 1: 100x^3 + 50x^2 + 25x + 10
    poly1.addTerm(100, 3); // $100 for premium service (level 3)
    poly1.addTerm(50, 2);  // $50 for standard service (level 2)
    poly1.addTerm(25, 1);  // $25 for basic service (level 1)
    poly1.addTerm(10, 0);  // $10 base fee
    
    // For customer 2: 75x^3 + 60x^2 + 30x + 15
    poly2.addTerm(75, 3);  // $75 for premium service (level 3)
    poly2.addTerm(60, 2);  // $60 for standard service (level 2)
    poly2.addTerm(30, 1);  // $30 for basic service (level 1)
    poly2.addTerm(15, 0);  // $15 base fee
    
    // Compare the billing histories
    PolynomialLinkedList::compare(poly1, poly2);
}

// Display all active tickets
void displayAllTickets() {
     cout << "\n----- Display All Active Tickets -----\n";
    ticketList.displayAllTickets();
}