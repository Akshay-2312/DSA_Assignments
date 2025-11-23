# Assignment Report

## Overview

Student Result Management System implementing hashing, searching, and sorting with performance analysis.

## ADT

StudentRecord: `StudentID`, `StudentName`, `Marks`, `CourseDetails`.

## Hashing

Separate chaining with `vector<list<StudentRecord>>`; hash function `id % table_size`.

## Searching

Sequential search `O(n)`; Binary search `O(log n)` on list sorted by roll number via radix sort.

## Sorting

- Heap Sort (marks)
- Quick Sort (marks)
- Radix Sort (roll numbers)

## Performance

Measured on datasets of 100, 1000, 10000 records. CSV exported to `screenshots/performance_chart.csv`.

## Complexity

- Hash insert/search: average `O(1)`, worst `O(n)` per bucket
- Sequential search: `O(n)`
- Binary search: `O(log n)`
- Heap Sort: `O(n log n)`
- Quick Sort: average `O(n log n)`
- Radix Sort: `O(d(n + k))`

## Screenshots

Use saved text outputs in `screenshots/` and export to images if needed.
