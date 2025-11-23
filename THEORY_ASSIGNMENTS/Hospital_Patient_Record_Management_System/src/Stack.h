#ifndef STACK_H
#define STACK_H

#include <cstddef>
using namespace std;

class UndoStack {
private:
    struct Node {
        int patientID;
        Node* next;
        Node(int id) : patientID(id), next(nullptr) {}
    };

    Node* top_;
    size_t size_;

public:
    UndoStack() : top_(nullptr), size_(0) {}

    ~UndoStack() { clear(); }

    void clear() {
        Node* cur = top_;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        top_ = nullptr;
        size_ = 0;
    }

    bool push(int patientID) {
        Node* node = new (nothrow) Node(patientID);
        if (!node) return false;
        node->next = top_;
        top_ = node;
        ++size_;
        return true;
    }

    bool pop(int& patientID) {
        if (!top_) return false;
        Node* node = top_;
        patientID = node->patientID;
        top_ = node->next;
        delete node;
        --size_;
        return true;
    }

    bool isEmpty() const { return top_ == nullptr; }
    size_t size() const { return size_; }
};

#endif