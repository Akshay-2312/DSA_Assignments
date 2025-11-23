#pragma once
#include <vector>
#include <algorithm>
#include "StudentRecord.h"
using namespace std;

// Bubble Sort by grade (ascending)
inline void bubbleSortGrades( vector<StudentRecord>& arr) {
    bool swapped;
    for (size_t i = 0; i < arr.size(); ++i) {
        swapped = false;
        for (size_t j = 0; j + 1 < arr.size() - i; ++j) {
            if (arr[j].grade > arr[j+1].grade) {  swap(arr[j], arr[j+1]); swapped = true; }
        }
        if (!swapped) break;
    }
}

// Insertion Sort by grade (ascending)
inline void insertionSortGrades( vector<StudentRecord>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        StudentRecord key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j-1].grade > key.grade) { arr[j] = arr[j-1]; --j; }
        arr[j] = key;
    }
}

// Merge Sort by grade (ascending)
inline void merge( vector<StudentRecord>& arr, size_t l, size_t m, size_t r) {
    size_t n1 = m - l + 1, n2 = r - m;
     vector<StudentRecord> L(n1), R(n2);
    for (size_t i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (size_t j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    size_t i = 0, j = 0; size_t k = l;
    while (i < n1 && j < n2) {
        if (L[i].grade <= R[j].grade) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

inline void mergeSortGradesImpl( vector<StudentRecord>& arr, size_t l, size_t r) {
    if (l >= r) return;
    size_t m = l + (r - l) / 2;
    mergeSortGradesImpl(arr, l, m);
    mergeSortGradesImpl(arr, m + 1, r);
    merge(arr, l, m, r);
}
inline void mergeSortGrades( vector<StudentRecord>& arr) {
    if (!arr.empty()) mergeSortGradesImpl(arr, 0, arr.size() - 1);
}

// Quick Sort by grade (ascending)
inline size_t partitionGrades( vector<StudentRecord>& arr, size_t low, size_t high) {
    double pivot = arr[high].grade;
    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        if (arr[j].grade < pivot) {  swap(arr[i], arr[j]); ++i; }
    }
     swap(arr[i], arr[high]);
    return i;
}
inline void quickSortGradesImpl( vector<StudentRecord>& arr, size_t low, size_t high) {
    if (low >= high) return;
    size_t pi = partitionGrades(arr, low, high);
    if (pi > 0) quickSortGradesImpl(arr, low, pi - 1);
    quickSortGradesImpl(arr, pi + 1, high);
}
inline void quickSortGrades( vector<StudentRecord>& arr) {
    if (!arr.empty()) quickSortGradesImpl(arr, 0, arr.size() - 1);
}

// Heap Sort by grade (descending for ranking)
inline void heapSortGradesDesc( vector<StudentRecord>& arr) {
    auto cmp = [](const StudentRecord& a, const StudentRecord& b){ return a.grade < b.grade; };
     make_heap(arr.begin(), arr.end(), cmp); // max-heap by grade
     vector<StudentRecord> sorted;
    while (!arr.empty()) {
         pop_heap(arr.begin(), arr.end(), cmp);
        sorted.push_back(arr.back());
        arr.pop_back();
    }
    arr = sorted; // now descending by grade
}