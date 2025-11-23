#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "TicketADT.h"
#include <iostream>
using namespace std;

// Node structure for singly linked list
struct Node {
    Ticket data;
    Node* next;
    
    // Constructor
    Node(const Ticket& ticket) : data(ticket), next(nullptr) {}
};

// Singly Linked List implementation for tickets
class LinkedList {
private:
    Node* head;
    int size;

public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}
    
    // Destructor
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // Insert a new ticket (at the end of the list)
    // Time Complexity: O(1) if we maintain a tail pointer, O(n) otherwise
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
    
    // Delete a ticket by ID
    // Time Complexity: O(n)
    bool deleteTicket(int ticketID) {
        if (head == nullptr) {
            return false;
        }
        
        if (head->data.getTicketID() == ticketID) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data.getTicketID() != ticketID) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            return false;
        }
        
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
        return true;
    }
    
    // Retrieve a ticket by ID
    // Time Complexity: O(n)
    Ticket* retrieveTicket(int ticketID) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.getTicketID() == ticketID) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
    
    // Display all tickets
    void displayAllTickets() {
        if (head == nullptr) {
             cout << "No tickets available." <<  endl;
            return;
        }
        
        Node* current = head;
         cout << "\n===== ACTIVE TICKETS =====\n";
        while (current != nullptr) {
             cout << "Ticket ID: " << current->data.getTicketID() <<  endl;
             cout << "Customer: " << current->data.getCustomerName() <<  endl;
             cout << "Issue: " << current->data.getIssueDescription() <<  endl;
             cout << "Priority: " << current->data.getPriority() <<  endl;
             cout << "------------------------" <<  endl;
            current = current->next;
        }
    }
    
    // Get the size of the list
    int getSize() const {
        return size;
    }
    
    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Get the head node (for iterating through the list)
    Node* getHead() const {
        return head;
    }
};

#endif // LINKED_LIST_H