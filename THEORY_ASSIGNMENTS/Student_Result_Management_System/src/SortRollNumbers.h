#pragma once
#include <vector>
#include <array>
#include "StudentRecord.h"

inline int maxID(const std::vector<StudentRecord>& a) {
    int m = 0;
    for (const auto& x : a) if (x.StudentID > m) m = x.StudentID;
    return m;
}

inline std::vector<StudentRecord> radixSortByID(std::vector<StudentRecord> a) {
    if (a.empty()) return a;
    int m = maxID(a);
    int exp = 1;
    std::vector<StudentRecord> output(a.size());
    while (m / exp > 0) {
        std::array<int, 10> count{};
        for (const auto& x : a) { int d = (x.StudentID / exp) % 10; ++count[d]; }
        for (int i = 1; i < 10; ++i) count[i] += count[i-1];
        for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
            int d = (a[i].StudentID / exp) % 10;
            output[--count[d]] = a[i];
        }
        a = output;
        exp *= 10;
    }
    return a;
}