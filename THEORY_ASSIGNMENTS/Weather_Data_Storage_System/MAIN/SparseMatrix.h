#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <vector>
#include <unordered_map>
#include "WeatherRecord.h"

using namespace std;

// Structure to represent a cell in sparse matrix (3-tuple form)
struct MatrixCell {
    int row;    // Year index
    int col;    // City index
    double value; // Temperature value
    
    MatrixCell(int r, int c, double v) : row(r), col(c), value(v) {}
};

class SparseMatrix {
private:
    // Vector to store non-sentinel values in 3-tuple form
    vector<MatrixCell> cells;
    
    // Maps for quick lookup
    unordered_map<int, unordered_map<int, double>> valueMap;
    
    // Sentinel value
    const double SENTINEL_VALUE = -999.0;
    
    // Reference to city and year mappings
    vector<string> cities;
    vector<int> years;

public:
    // Constructor
    SparseMatrix(const vector<string>& cityList, const vector<int>& yearList, 
                 const double weatherTable[][20], int maxYears, int maxCities) 
        : cities(cityList), years(yearList) {
        
        // Convert dense matrix to sparse representation
        for (int i = 0; i < years.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (weatherTable[i][j] != SENTINEL_VALUE) {
                    cells.push_back(MatrixCell(i, j, weatherTable[i][j]));
                    valueMap[i][j] = weatherTable[i][j];
                }
            }
        }
    }
    
    // Insert a value
    void insert(int yearIdx, int cityIdx, double value) {
        // Check if the cell already exists
        auto it = valueMap.find(yearIdx);
        if (it != valueMap.end() && it->second.find(cityIdx) != it->second.end()) {
            // Update existing cell
            for (auto& cell : cells) {
                if (cell.row == yearIdx && cell.col == cityIdx) {
                    cell.value = value;
                    break;
                }
            }
            valueMap[yearIdx][cityIdx] = value;
        } else {
            // Add new cell
            cells.push_back(MatrixCell(yearIdx, cityIdx, value));
            valueMap[yearIdx][cityIdx] = value;
        }
    }
    
    // Delete a value
    bool deleteValue(int yearIdx, int cityIdx) {
        auto it = valueMap.find(yearIdx);
        if (it != valueMap.end() && it->second.find(cityIdx) != it->second.end()) {
            // Remove from valueMap
            it->second.erase(cityIdx);
            if (it->second.empty()) {
                valueMap.erase(yearIdx);
            }
            
            // Remove from cells vector
            for (auto cell = cells.begin(); cell != cells.end(); ++cell) {
                if (cell->row == yearIdx && cell->col == cityIdx) {
                    cells.erase(cell);
                    return true;
                }
            }
        }
        return false;
    }
    
    // Retrieve a value
    double retrieve(int yearIdx, int cityIdx) const {
        auto it = valueMap.find(yearIdx);
        if (it != valueMap.end()) {
            auto it2 = it->second.find(cityIdx);
            if (it2 != it->second.end()) {
                return it2->second;
            }
        }
        return SENTINEL_VALUE;
    }
    
    // Get all non-sentinel values as WeatherRecord objects
    vector<WeatherRecord> getAllRecords() const {
        vector<WeatherRecord> records;
        for (const auto& cell : cells) {
            if (cell.row < years.size() && cell.col < cities.size()) {
                // Create a date string (simplified for this example)
                string date = "01/01/" + to_string(years[cell.row]);
                WeatherRecord record(date, cities[cell.col], cell.value);
                records.push_back(record);
            }
        }
        return records;
    }
    
    // Get the number of non-sentinel values
    size_t getSize() const {
        return cells.size();
    }
    
    // Get memory usage estimation
    size_t getMemoryUsage() const {
        // Each MatrixCell has 2 ints (8 bytes) and 1 double (8 bytes)
        return cells.size() * (sizeof(int) * 2 + sizeof(double));
    }
    
    // Print the sparse matrix representation
    void printSparseMatrix() const {
        cout << "Sparse Matrix Representation (3-tuple form):" << endl;
        cout << "Row\tColumn\tValue" << endl;
        for (const auto& cell : cells) {
            cout << cell.row << "\t" << cell.col << "\t" << cell.value << endl;
        }
        cout << "Total non-sentinel elements: " << cells.size() << endl;
    }
};

#endif // SPARSE_MATRIX_H