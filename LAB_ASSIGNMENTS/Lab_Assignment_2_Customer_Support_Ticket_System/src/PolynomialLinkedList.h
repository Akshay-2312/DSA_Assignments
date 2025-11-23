#ifndef POLYNOMIAL_LINKED_LIST_H
#define POLYNOMIAL_LINKED_LIST_H

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Node structure for polynomial linked list
struct PolyNode {
    int coefficient;
    int exponent;
    PolyNode* next;
    
    // Constructor
    PolyNode(int coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}
};

// Polynomial Linked List implementation for billing history
class PolynomialLinkedList {
private:
    PolyNode* head;
     string customerName;

public:
    // Constructor
    PolynomialLinkedList(const  string& name = "") : head(nullptr), customerName(name) {}
    
    // Destructor
    ~PolynomialLinkedList() {
        PolyNode* current = head;
        while (current != nullptr) {
            PolyNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // Get customer name
     string getCustomerName() const {
        return customerName;
    }
    
    // Set customer name
    void setCustomerName(const  string& name) {
        customerName = name;
    }
    
    // Add a term to the polynomial
    // Time Complexity: O(n)
    void addTerm(int coefficient, int exponent) {
        if (coefficient == 0) {
            return; // Ignore zero coefficients
        }
        
        PolyNode* newNode = new PolyNode(coefficient, exponent);
        
        // If list is empty or new term has higher exponent than head
        if (head == nullptr || exponent > head->exponent) {
            newNode->next = head;
            head = newNode;
            return;
        }
        
        // Find the correct position to insert
        PolyNode* current = head;
        while (current->next != nullptr && current->next->exponent > exponent) {
            current = current->next;
        }
        
        // If term with same exponent exists, add coefficients
        if (current->exponent == exponent) {
            current->coefficient += coefficient;
            delete newNode;
            
            // Remove the term if coefficient becomes zero
            if (current->coefficient == 0) {
                if (current == head) {
                    head = head->next;
                    delete current;
                } else {
                    PolyNode* prev = head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    prev->next = current->next;
                    delete current;
                }
            }
        } else if (current->next != nullptr && current->next->exponent == exponent) {
            current->next->coefficient += coefficient;
            delete newNode;
            
            // Remove the term if coefficient becomes zero
            if (current->next->coefficient == 0) {
                PolyNode* temp = current->next;
                current->next = temp->next;
                delete temp;
            }
        } else {
            // Insert the new term
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    
    // Add two polynomials
    // Time Complexity: O(m + n)
    static PolynomialLinkedList add(const PolynomialLinkedList& p1, const PolynomialLinkedList& p2) {
        PolynomialLinkedList result;
        
        PolyNode* current = p1.head;
        while (current != nullptr) {
            result.addTerm(current->coefficient, current->exponent);
            current = current->next;
        }
        
        current = p2.head;
        while (current != nullptr) {
            result.addTerm(current->coefficient, current->exponent);
            current = current->next;
        }
        
        return result;
    }
    
    // Compare two polynomials
    // Time Complexity: O(m + n)
    static void compare(const PolynomialLinkedList& p1, const PolynomialLinkedList& p2) {
         cout << "\n===== BILLING HISTORY COMPARISON =====\n";
         cout << "Customer 1: " << p1.customerName <<  endl;
         cout << "Customer 2: " << p2.customerName <<  endl;
        
        // Calculate total value for each polynomial at x = 1
        int total1 = 0;
        int total2 = 0;
        
        PolyNode* current = p1.head;
        while (current != nullptr) {
            total1 += current->coefficient; // When x = 1, x^n = 1
            current = current->next;
        }
        
        current = p2.head;
        while (current != nullptr) {
            total2 += current->coefficient; // When x = 1, x^n = 1
            current = current->next;
        }
        
         cout << "Total billing for " << p1.customerName << ": $" << total1 <<  endl;
         cout << "Total billing for " << p2.customerName << ": $" << total2 <<  endl;
        
        if (total1 > total2) {
             cout << p1.customerName << " has higher billing by $" << (total1 - total2) <<  endl;
        } else if (total2 > total1) {
             cout << p2.customerName << " has higher billing by $" << (total2 - total1) <<  endl;
        } else {
             cout << "Both customers have equal billing totals." <<  endl;
        }
        
        // Display the polynomial expressions
         cout << "\nBilling polynomial for " << p1.customerName << ": ";
        p1.display();
        
         cout << "Billing polynomial for " << p2.customerName << ": ";
        p2.display();
        
         cout << "====================================\n";
    }
    
    // Display the polynomial
    void display() const {
        if (head == nullptr) {
             cout << "0" <<  endl;
            return;
        }
        
        PolyNode* current = head;
        bool isFirst = true;
        
        while (current != nullptr) {
            if (current->coefficient > 0 && !isFirst) {
                 cout << " + ";
            } else if (current->coefficient < 0) {
                 cout << " - ";
            }
            
            if (isFirst && current->coefficient < 0) {
                 cout << "-";
            }
            
            int absCoef =  abs(current->coefficient);
            if (absCoef != 1 || current->exponent == 0) {
                 cout << absCoef;
            }
            
            if (current->exponent > 0) {
                 cout << "x";
                if (current->exponent > 1) {
                     cout << "^" << current->exponent;
                }
            }
            
            isFirst = false;
            current = current->next;
        }
        
         cout <<  endl;
    }
};

#endif // POLYNOMIAL_LINKED_LIST_H