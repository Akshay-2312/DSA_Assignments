# Student Result Management System

A menu-driven C++ program implementing hashing with collision handling, searching, sorting (heap/quick/radix), and performance comparison.

## Build

- `g++ -std=c++17 -O2 -o StudentResultSystem.exe src\main.cpp`

## Run

- `./StudentResultSystem.exe`

## Menu

- 1 Add record
- 2 Search record (sequential or binary)
- 3 Sort by marks (heap/quick)
- 4 Sort by roll number (radix)
- 5 Compare sorting algorithms (console)
- 6 Display sorted list
- 7 Exit
- 8 Generate sample datasets (creates `data/*.txt`)
- 9 Export performance CSV (writes `screenshots/performance_chart.csv`)
- 10 Save sorted list to file (writes `screenshots/sorted_*.txt`)

## Folders

- `src/` code
- `data/` sample datasets (generated via menu option 8)
- `docs/` put final PDF reports
- `screenshots/` program-exported CSV and text outputs

## Notes

- Binary search sorts by roll number using radix sort before searching.
- Hash table uses separate chaining.
- Performance uses synthetic data for 100/1000/10000 records; export to CSV via option 9.

## License

- MIT (see LICENSE)