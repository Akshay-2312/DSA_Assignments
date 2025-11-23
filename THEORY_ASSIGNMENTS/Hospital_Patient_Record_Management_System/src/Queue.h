#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

struct EmergencyPatient {
    int patientID;
    string name;
    int severity;
};

class CircularQueue {
private:
    vector<EmergencyPatient> data;
    size_t head;
    size_t tail;
    size_t count;

public:
    explicit CircularQueue(size_t capacity = 32)
        : data(capacity), head(0), tail(0), count(0) {}

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == data.size(); }
    size_t size() const { return count; }
    size_t capacity() const { return data.size(); }

    void resize(size_t newCap) {
        if (newCap < count) throw runtime_error("New capacity smaller than current size");
        vector<EmergencyPatient> newData(newCap);
        for (size_t i = 0; i < count; ++i) {
            newData[i] = data[(head + i) % data.size()];
        }
        data.swap(newData);
        head = 0;
        tail = count % data.size();
    }

    bool enqueue(const EmergencyPatient& p) {
        if (isFull()) resize(data.size() * 2);
        data[tail] = p;
        tail = (tail + 1) % data.size();
        ++count;
        return true;
    }

    bool dequeue(EmergencyPatient& out) {
        if (isEmpty()) return false;
        out = data[head];
        head = (head + 1) % data.size();
        --count;
        return true;
    }
};

class PriorityQueue {
private:
    vector<EmergencyPatient> heap;

    static bool less(const EmergencyPatient& a, const EmergencyPatient& b) {
        return a.severity < b.severity;
    }

    void heapifyUp(size_t idx) {
        while (idx > 0) {
            size_t parent = (idx - 1) / 2;
            if (!less(heap[parent], heap[idx])) break;
            swap(heap[parent], heap[idx]);
            idx = parent;
        }
    }

    void heapifyDown(size_t idx) {
        size_t n = heap.size();
        while (true) {
            size_t left = 2 * idx + 1;
            size_t right = 2 * idx + 2;
            size_t largest = idx;
            if (left < n && less(heap[largest], heap[left])) largest = left;
            if (right < n && less(heap[largest], heap[right])) largest = right;
            if (largest == idx) break;
            swap(heap[idx], heap[largest]);
            idx = largest;
        }
    }

public:
    bool isEmpty() const { return heap.empty(); }
    size_t size() const { return heap.size(); }

    bool enqueue(const EmergencyPatient& p) {
        heap.push_back(p);
        heapifyUp(heap.size() - 1);
        return true;
    }

    bool dequeue(EmergencyPatient& out) {
        if (heap.empty()) return false;
        out = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return true;
    }
};

enum class EmergencyQueueType { Circular, Priority };

class EmergencyQueueManager {
private:
    EmergencyQueueType type;
    CircularQueue circular;
    PriorityQueue priority;

public:
    explicit EmergencyQueueManager(EmergencyQueueType t = EmergencyQueueType::Priority)
        : type(t), circular(32), priority() {}

    void setType(EmergencyQueueType t) { type = t; }
    EmergencyQueueType getType() const { return type; }

    bool enqueue(const EmergencyPatient& p) {
        if (type == EmergencyQueueType::Circular) return circular.enqueue(p);
        return priority.enqueue(p);
    }

    bool dequeue(EmergencyPatient& out) {
        if (type == EmergencyQueueType::Circular) return circular.dequeue(out);
        return priority.dequeue(out);
    }

    size_t size() const {
        if (type == EmergencyQueueType::Circular) return circular.size();
        return priority.size();
    }

    void printPeek() const {
        std::cout << "Queue size: " << size() << '\n';
    }
};

#endif