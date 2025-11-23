#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "StudentRecord.h"
using namespace std;

class HashTable {
private:
     vector< list<StudentRecord>> buckets;
    size_t capacity;

    size_t hashID(int id) const { return static_cast<size_t>(id) % capacity; }
    size_t hashName(const  string& name) const {
        size_t h = 0; for (char c : name) h = h * 131 + static_cast<unsigned char>(c); return h % capacity;
    }

public:
    explicit HashTable(size_t cap = 101) : capacity(cap) { buckets.resize(capacity); }

    // Insert with separate chaining
    void insert(const StudentRecord& rec) {
        buckets[hashID(rec.studentID)].push_back(rec);
    }

    // Search by ID
    const StudentRecord* searchByID(int id) const {
        size_t idx = hashID(id);
        for (const auto& rec : buckets[idx]) {
            if (rec.studentID == id) return &rec;
        }
        return nullptr;
    }

    // Search by name (returns all matches)
     vector<StudentRecord> searchByName(const  string& name) const {
         vector<StudentRecord> results;
        // We can either hash by name or scan all buckets; we scan for robust matching
        for (const auto& bucket : buckets) {
            for (const auto& rec : bucket) {
                if (rec.studentName == name) results.push_back(rec);
            }
        }
        return results;
    }

    // View hash table (buckets and collisions)
    void display() const {
         cout << "Hash Table View (bucket -> entries):\n";
        for (size_t i = 0; i < capacity; ++i) {
             cout << i << ": ";
            if (buckets[i].empty()) {  cout << "-"; }
            else {
                bool first = true;
                for (const auto& rec : buckets[i]) {
                    if (!first)  cout << " | ";
                     cout << "[" << rec.studentID << ", " << rec.studentName << ", " << rec.grade << "]";
                    first = false;
                }
            }
             cout << "\n";
        }
    }
};