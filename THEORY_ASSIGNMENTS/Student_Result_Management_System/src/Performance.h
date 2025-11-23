#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include "StudentRecord.h"
#include "Utils.h"
#include "SortMarks.h"
#include "SortRollNumbers.h"

inline long long timeHeapSortMarks(const std::vector<StudentRecord>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    auto sorted = heapSortByMarks(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

inline long long timeQuickSortMarks(const std::vector<StudentRecord>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    auto sorted = quickSortByMarks(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

inline long long timeRadixSortIDs(const std::vector<StudentRecord>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    auto sorted = radixSortByID(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

inline void compareSortingPerformance() {
    std::vector<size_t> sizes = {100, 1000, 10000};
    std::cout << "DatasetSize | HeapMarks(ms) | QuickMarks(ms) | RadixIDs(ms)\n";
    for (size_t n : sizes) {
        auto data = generateRandomRecords(n);
        long long t1 = timeHeapSortMarks(data);
        long long t2 = timeQuickSortMarks(data);
        long long t3 = timeRadixSortIDs(data);
        std::cout << n << " | " << t1 << " | " << t2 << " | " << t3 << "\n";
    }
}

inline bool compareSortingPerformanceCsv(const std::string& path) {
    std::vector<size_t> sizes = {100, 1000, 10000};
    std::ofstream fout(path);
    if (!fout) return false;
    fout << "DatasetSize,HeapMarks(ms),QuickMarks(ms),RadixIDs(ms)\n";
    for (size_t n : sizes) {
        auto data = generateRandomRecords(n);
        long long t1 = timeHeapSortMarks(data);
        long long t2 = timeQuickSortMarks(data);
        long long t3 = timeRadixSortIDs(data);
        fout << n << "," << t1 << "," << t2 << "," << t3 << "\n";
    }
    return true;
}