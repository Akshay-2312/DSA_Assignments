#pragma once
#include <vector>
#include <random>
#include "StudentRecord.h"

inline void heapifyByMarks(std::vector<StudentRecord>& a, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && a[l].Marks > a[largest].Marks) largest = l;
    if (r < n && a[r].Marks > a[largest].Marks) largest = r;
    if (largest != i) { std::swap(a[i], a[largest]); heapifyByMarks(a, n, largest); }
}

inline std::vector<StudentRecord> heapSortByMarks(std::vector<StudentRecord> a) {
    int n = static_cast<int>(a.size());
    for (int i = n/2 - 1; i >= 0; --i) heapifyByMarks(a, n, i);
    for (int i = n - 1; i > 0; --i) { std::swap(a[0], a[i]); heapifyByMarks(a, i, 0); }
    return a;
}

inline int partitionByMarks(std::vector<StudentRecord>& a, int low, int high) {
    double pivot = a[high].Marks;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (a[j].Marks <= pivot) { ++i; std::swap(a[i], a[j]); }
    }
    std::swap(a[i+1], a[high]);
    return i + 1;
}

inline void quickSortByMarksRec(std::vector<StudentRecord>& a, int low, int high) {
    if (low < high) {
        int pi = partitionByMarks(a, low, high);
        quickSortByMarksRec(a, low, pi - 1);
        quickSortByMarksRec(a, pi + 1, high);
    }
}

inline std::vector<StudentRecord> quickSortByMarks(std::vector<StudentRecord> a) {
    if (!a.empty()) quickSortByMarksRec(a, 0, static_cast<int>(a.size()) - 1);
    return a;
}