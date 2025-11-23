# Sorting Performance

## Methods

- Heap Sort (Marks)
- Quick Sort (Marks)
- Radix Sort (Roll Numbers)

## Measurement

`std::chrono::high_resolution_clock` across datasets of 100, 1000, 10000 records.

## Export

Use menu option 9 to export `screenshots/performance_chart.csv`.

## Observations

On typical runs, Quick Sort and Radix Sort are fast for large datasets; Heap Sort is consistent.
