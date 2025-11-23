#ifndef TICKET_ADT_H
#define TICKET_ADT_H

#include <string>
#include <iostream>
using namespace std;

// Ticket ADT class
class Ticket {
private:
    int ticketID;
    string customerName;
    string issueDescription;
    int priority; // 1 = urgent, 2 = normal, etc.

public:
    // Default constructor
    Ticket() : ticketID(0), customerName(""), issueDescription(""), priority(0) {}
    
    // Constructor
    Ticket(int id, const string& name, const string& issue, int prio) 
        : ticketID(id), customerName(name), issueDescription(issue), priority(prio) {}

    // Getters
    int getTicketID() const { return ticketID; }
    string getCustomerName() const { return customerName; }
    string getIssueDescription() const { return issueDescription; }
    int getPriority() const { return priority; }

    // Setters
    void setTicketID(int id) { ticketID = id; }
    void setCustomerName(const string& name) { customerName = name; }
    void setIssueDescription(const string& issue) { issueDescription = issue; }
    void setPriority(int prio) { priority = prio; }
};

#endif // TICKET_ADT_H