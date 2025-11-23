# Weather Data Storage System

A C++ implementation of a system for collecting, storing, and managing weather data using Abstract Data Types (ADTs) and 2D Arrays.

## Project Overview

This project implements a Weather Data Storage System that:
- Collects, stores, and manages weather data (temperature, city, date)
- Uses Abstract Data Types (ADTs) and 2D Arrays
- Handles both complete and sparse datasets
- Allows insertion, retrieval, and deletion of records efficiently

## Features

- **WeatherRecord ADT**: Stores date, city, and temperature data
- **2D Array Storage**: Efficiently stores temperature data by year and city
- **Row-Major & Column-Major Access**: Demonstrates different memory access patterns
- **Sparse Data Handling**: Uses 3-tuple representation for efficient storage
- **Complexity Analysis**: Compares time and space complexity of operations

## Algorithms Used

1. **Row-Major Access**: 
   - Index Formula: `index = row * total_columns + column`
   - Time Complexity: O(n × m)

2. **Column-Major Access**:
   - Index Formula: `index = column * total_rows + row`
   - Time Complexity: O(n × m)

3. **Sparse Matrix Representation**:
   - 3-tuple form: (row, col, value)
   - Only stores non-sentinel values
   - Space Complexity: O(k) where k = non-zero elements

## Compilation Steps

To compile the program:

```bash
g++ src/main.cpp -o weather_system
```

To run the program:

```bash
./weather_system
```

## Project Structure

```
📦 Weather_Data_Storage_System/
│
├── 📁 src/
│   ├── main.cpp                  # Main driver program (menu-driven)
│   ├── WeatherRecord.h           # ADT definition
│   ├── DataStorage.h             # 2D array storage + access logic
│   ├── SparseMatrix.h            # Sparse representation handler
│
├── 📁 reports/
│   ├── Implementation_Report.pdf # Detailed explanation
│   ├── Complexity_Analysis.pdf   # Time & space complexity comparison
│
├── 📁 screenshots/
│   ├── output_row_major.png
│   ├── output_column_major.png
│   ├── output_sparse_data.png
│
└── README.md                     # Project overview (this file)
```

## Operation Complexities

| Operation | Description | Time | Space |
|-----------|-------------|------|-------|
| insert() | Add new record | O(1) | O(n × m) |
| delete() | Remove record by city/date | O(1) | O(n × m) |
| retrieve() | Lookup by city and year | O(1) | O(n × m) |
| rowMajorAccess() | Sequential traversal row-wise | O(n × m) | O(1) |
| columnMajorAccess() | Sequential traversal column-wise | O(n × m) | O(1) |
| handleSparseData() | Convert to sparse representation | O(n × m) | O(k) |

Where:
- n = number of years
- m = number of cities
- k = number of non-sentinel elements