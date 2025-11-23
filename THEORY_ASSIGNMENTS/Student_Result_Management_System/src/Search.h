#pragma once
#include <vector>
#include "StudentRecord.h"

inline int sequentialSearch(const std::vector<StudentRecord>& v, int id) {
    for (size_t i = 0; i < v.size(); ++i) if (v[i].StudentID == id) return static_cast<int>(i);
    return -1;
}

inline int binarySearch(const std::vector<StudentRecord>& v, int id) {
    int l = 0, r = static_cast<int>(v.size()) - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (v[m].StudentID == id) return m;
        if (v[m].StudentID < id) l = m + 1; else r = m - 1;
    }
    return -1;
}