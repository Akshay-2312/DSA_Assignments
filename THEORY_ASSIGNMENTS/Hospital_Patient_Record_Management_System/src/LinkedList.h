#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "PatientRecord.h"
using namespace std;

class LinkedList {
private:
    struct Node {
        PatientRecord data;
        Node* next;
        Node(const PatientRecord& pr) : data(pr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size_;

public:
    LinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    ~LinkedList() { clear(); }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    size_t size() const { return size_; }

    bool insertPatient(const PatientRecord& record) {
        Node* node = new (nothrow) Node(record);
        if (!node) return false;
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++size_;
        return true;
    }

    bool deletePatient(int patientID) {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur) {
            if (cur->data.patientID == patientID) {
                if (prev) prev->next = cur->next; else head = cur->next;
                if (cur == tail) tail = prev;
                delete cur;
                --size_;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    bool retrievePatient(int patientID, PatientRecord& out) const {
        Node* cur = head;
        while (cur) {
            if (cur->data.patientID == patientID) { out = cur->data; return true; }
            cur = cur->next;
        }
        return false;
    }

    void printAll() const {
        if (!head) {
            cout << "No patient records.\n";
            return;
        }
        Node* cur = head;
        while (cur) {
            const PatientRecord& p = cur->data;
            cout << "ID: " << p.patientID
                 << ", Name: " << p.patientName
                 << ", Date: " << p.admissionDate
                 << ", Treatment: " << p.treatmentDetails << '\n';
            cur = cur->next;
        }
    }
};

#endif