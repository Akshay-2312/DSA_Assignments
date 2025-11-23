# Lab Assignment 3: Student Performance Tracker

## Overview
- Theme: Sorting, Searching, and Hashing
- Goal: Store, sort, search student data; rank by grades; handle duplicates via hashing; compare sorting algorithms.

## Directory Structure
```
Lab_Assignment_3_Student_Performance_Tracker/
├── src/
│   ├── main.cpp
│   ├── SortingAlgorithms.h
│   ├── HashTable.h
│   └── StudentRecord.h
├── reports/
│   ├── Complexity_Analysis.md (export to PDF)
│   └── Implementation_Report.md (export to PDF)
├── screenshots/
│   ├── output_1_add_student.png (placeholder)
│   ├── output_2_search.png (placeholder)
│   └── output_3_ranking.png (placeholder)
└── README.md
```

## Build & Run
- Requirements: `g++` C++17
- Build: `g++ -std=c++17 src/main.cpp -o student_tracker.exe`
- Run: `./student_tracker.exe`

## Features
- Add student record (hash + array)
- Search by ID/name (sequential/binary)
- Sort by grades (bubble, insertion, merge, quick)
- Rank by grades (heap sort)
- Hash table view (separate chaining collisions)
- Complexity comparison table

## Data Structures
- HashTable: separate chaining using `vector<list<StudentRecord>>`
- StudentArray: `vector<StudentRecord>` for sorting/searching
- SortedList: `vector<StudentRecord>` produced by chosen sort

## Notes
- Reports are provided as `.md` for easy editing; export to PDF for submission.
- Screenshot files are placeholders—replace with real captures after running.

## Author
- Name: < Akshay yadav >
- ID: < 2401730129 >
- Course: < DATA STRUCTURES >
