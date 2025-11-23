#pragma once
#include <vector>
#include <list>
#include <optional>
#include "StudentRecord.h"

class HashTable {
    size_t table_size;
    std::vector<std::list<StudentRecord>> buckets;
    size_t hash(int id) const { return static_cast<size_t>(id) % table_size; }
public:
    explicit HashTable(size_t size = 1031) : table_size(size), buckets(size) {}
    bool insertStudent(const StudentRecord& s) {
        if (exists(s.StudentID)) return false;
        buckets[hash(s.StudentID)].push_back(s);
        return true;
    }
    std::optional<StudentRecord> searchStudent(int id) const {
        const auto& bucket = buckets[hash(id)];
        for (const auto& x : bucket) if (x.StudentID == id) return x;
        return std::nullopt;
    }
    bool exists(int id) const { return searchStudent(id).has_value(); }
    std::vector<StudentRecord> toVector() const {
        std::vector<StudentRecord> v;
        for (const auto& bucket : buckets) for (const auto& x : bucket) v.push_back(x);
        return v;
    }
};