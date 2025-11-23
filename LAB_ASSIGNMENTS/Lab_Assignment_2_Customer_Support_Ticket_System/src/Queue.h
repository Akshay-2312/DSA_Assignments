#ifndef QUEUE_H
#define QUEUE_H

#include "TicketADT.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

// Priority Queue implementation for urgent tickets
class PriorityQueue {
private:
     vector<Ticket> tickets;

public:
    // Add a ticket to the priority queue
    // Time Complexity: O(log n) due to heapify operation
    void enqueue(const Ticket& ticket) {
        tickets.push_back(ticket);
         push_heap(tickets.begin(), tickets.end(), 
            [](const Ticket& a, const Ticket& b) {
                return a.getPriority() > b.getPriority(); // Min heap based on priority
            });
    }
    
    // Remove the highest priority ticket
    // Time Complexity: O(log n)
    bool dequeue(Ticket& ticket) {
        if (tickets.empty()) {
            return false;
        }
        
         pop_heap(tickets.begin(), tickets.end(), 
            [](const Ticket& a, const Ticket& b) {
                return a.getPriority() > b.getPriority();
            });
        
        ticket = tickets.back();
        tickets.pop_back();
        return true;
    }
    
    // Check if the priority queue is empty
    bool isEmpty() const {
        return tickets.empty();
    }
    
    // Get the size of the priority queue
    size_t size() const {
        return tickets.size();
    }
    
    // Display all tickets in the priority queue
    void display() const {
        if (tickets.empty()) {
             cout << "No tickets in priority queue." <<  endl;
            return;
        }
        
         cout << "\n===== PRIORITY QUEUE TICKETS =====\n";
        // Create a copy to preserve the heap
         vector<Ticket> ticketsCopy = tickets;
         sort(ticketsCopy.begin(), ticketsCopy.end(), 
            [](const Ticket& a, const Ticket& b) {
                return a.getPriority() < b.getPriority();
            });
            
        for (const auto& ticket : ticketsCopy) {
             cout << "Ticket ID: " << ticket.getTicketID() <<  endl;
             cout << "Customer: " << ticket.getCustomerName() <<  endl;
             cout << "Issue: " << ticket.getIssueDescription() <<  endl;
             cout << "Priority: " << ticket.getPriority() <<  endl;
             cout << "------------------------" <<  endl;
        }
    }
};

// Circular Queue implementation for round-robin processing
class CircularQueue {
private:
    Ticket* tickets;
    int front;
    int rear;
    int capacity;
    int size;

public:
    // Constructor
    CircularQueue(int cap = 10) : capacity(cap), front(-1), rear(-1), size(0) {
        tickets = new Ticket[capacity];
    }
    
    // Destructor
    ~CircularQueue() {
        delete[] tickets;
    }
    
    // Add a ticket to the circular queue
    // Time Complexity: O(1)
    bool enqueue(const Ticket& ticket) {
        if (isFull()) {
            return false;
        }
        
        if (isEmpty()) {
            front = 0;
        }
        
        rear = (rear + 1) % capacity;
        tickets[rear] = ticket;
        size++;
        return true;
    }
    
    // Remove a ticket from the circular queue
    // Time Complexity: O(1)
    bool dequeue(Ticket& ticket) {
        if (isEmpty()) {
            return false;
        }
        
        ticket = tickets[front];
        
        if (front == rear) {
            // Last element
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        
        size--;
        return true;
    }
    
    // Check if the circular queue is full
    bool isFull() const {
        return size == capacity;
    }
    
    // Check if the circular queue is empty
    bool isEmpty() const {
        return front == -1;
    }
    
    // Get the size of the circular queue
    int getSize() const {
        return size;
    }
    
    // Display all tickets in the circular queue
    void display() const {
        if (isEmpty()) {
             cout << "No tickets in circular queue." <<  endl;
            return;
        }
        
         cout << "\n===== CIRCULAR QUEUE TICKETS =====\n";
        int count = 0;
        int index = front;
        
        while (count < size) {
             cout << "Ticket ID: " << tickets[index].getTicketID() <<  endl;
             cout << "Customer: " << tickets[index].getCustomerName() <<  endl;
             cout << "Issue: " << tickets[index].getIssueDescription() <<  endl;
             cout << "Priority: " << tickets[index].getPriority() <<  endl;
             cout << "------------------------" <<  endl;
            
            index = (index + 1) % capacity;
            count++;
        }
    }
};

#endif // QUEUE_H