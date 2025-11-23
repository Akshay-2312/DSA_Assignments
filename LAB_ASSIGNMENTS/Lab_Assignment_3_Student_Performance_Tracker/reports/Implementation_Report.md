# Implementation Report — Student Performance Tracker

## 1. Student Record ADT
- Attributes: `studentID (int)`, `studentName (string)`, `grade (double)`, `courseDetails (string)`
- Purpose: Encapsulates a single student record used across data structures.

## 2. Algorithms Implemented
- Searching:
  - Sequential search (ID, name)
  - Binary search (requires sorting by ID/name first)
- Sorting:
  - Bubble, Insertion, Merge, Quick (grades ascending)
  - Heap Sort (grades descending for ranking)
- Hashing:
  - Separate chaining (`vector<list<StudentRecord>>`) with modulo hashing on `studentID`

## 3. Collision Handling Strategy
- Separate chaining stores colliding entries in a list per bucket.
- Advantages: simple, scalable, avoids primary clustering; buckets resize by chosen capacity.

## 4. Complexity Comparison
- See `reports/Complexity_Analysis.md` for the full table.

## 5. Sample I/O Flow
1) Add student: ID=101, Name=Alice, Grade=95.2
2) Add student: ID=102, Name=Bob, Grade=88.5
3) Search by ID (binary): 101 → Found Alice
4) Sort by grades (merge): outputs ascending list
5) Rank by performance (heap sort): outputs descending list
6) View hash table: displays collisions and bucket entries

## 6. Conclusion
- Merge Sort provides consistent O(n log n) performance and is stable.
- Quick Sort is often fastest on average but degrades to O(n^2) in worst case.
- Heap Sort is ideal for ranking when only order is needed and stability is not required.
- Hashing with separate chaining maintains near O(1) average search/insert; performance depends on load factor.

> Export this document to PDF (`Implementation_Report.pdf`) for submission.