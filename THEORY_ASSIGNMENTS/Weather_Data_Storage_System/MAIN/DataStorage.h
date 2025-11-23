#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <vector>
#include <unordered_map>
#include <chrono>
#include "WeatherRecord.h"

using namespace std;

class DataStorage {
private:
    // Constants for array dimensions
    static const int MAX_YEARS = 10;  // Assuming 10 years of data
    static const int MAX_CITIES = 20; // Assuming 20 cities
    
    // 2D array to store temperature data
    double weatherTable[MAX_YEARS][MAX_CITIES];
    
    // Maps to store city and year indices
    unordered_map<string, int> cityToIndex;
    unordered_map<int, int> yearToIndex;
    
    // Vector to store city names and years for reverse lookup
    vector<string> cities;
    vector<int> years;
    
    // Sentinel value for missing data
    const double SENTINEL_VALUE = -999.0;
    
public:
    // Constructor
    DataStorage() {
        // Initialize the 2D array with sentinel values
        for (int i = 0; i < MAX_YEARS; i++) {
            for (int j = 0; j < MAX_CITIES; j++) {
                weatherTable[i][j] = SENTINEL_VALUE;
            }
        }
    }
    
    // Add a city to the system if it doesn't exist
    int addCity(const string& city) {
        if (cityToIndex.find(city) == cityToIndex.end()) {
            if (cities.size() >= MAX_CITIES) {
                return -1; // Maximum cities reached
            }
            int index = cities.size();
            cities.push_back(city);
            cityToIndex[city] = index;
            return index;
        }
        return cityToIndex[city];
    }
    
    // Add a year to the system if it doesn't exist
    int addYear(int year) {
        if (yearToIndex.find(year) == yearToIndex.end()) {
            if (years.size() >= MAX_YEARS) {
                return -1; // Maximum years reached
            }
            int index = years.size();
            years.push_back(year);
            yearToIndex[year] = index;
            return index;
        }
        return yearToIndex[year];
    }
    
    // Insert a weather record
    bool insert(const WeatherRecord& record) {
        int year = record.getYear();
        string city = record.getCity();
        
        int yearIdx = addYear(year);
        int cityIdx = addCity(city);
        
        if (yearIdx == -1 || cityIdx == -1) {
            return false; // Failed to add year or city
        }
        
        weatherTable[yearIdx][cityIdx] = record.getTemperature();
        return true;
    }
    
    // Delete a weather record
    bool deleteRecord(const string& city, int year) {
        if (cityToIndex.find(city) == cityToIndex.end() || 
            yearToIndex.find(year) == yearToIndex.end()) {
            return false; // City or year not found
        }
        
        int yearIdx = yearToIndex[year];
        int cityIdx = cityToIndex[city];
        
        weatherTable[yearIdx][cityIdx] = SENTINEL_VALUE;
        return true;
    }
    
    // Retrieve temperature for a specific city and year
    double retrieve(const string& city, int year) {
        if (cityToIndex.find(city) == cityToIndex.end() || 
            yearToIndex.find(year) == yearToIndex.end()) {
            return SENTINEL_VALUE; // City or year not found
        }
        
        int yearIdx = yearToIndex[year];
        int cityIdx = cityToIndex[city];
        
        return weatherTable[yearIdx][cityIdx];
    }
    
    // Row-major access (traverse by rows)
    vector<WeatherRecord> rowMajorAccess() {
        vector<WeatherRecord> result;
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = 0; i < years.size(); i++) {
            for (int j = 0; j < cities.size(); j++) {
                if (weatherTable[i][j] != SENTINEL_VALUE) {
                    // Create a date string (simplified for this example)
                    string date = "01/01/" + to_string(years[i]);
                    WeatherRecord record(date, cities[j], weatherTable[i][j]);
                    result.push_back(record);
                }
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "Row-major access time: " << duration.count() << " ms" << endl;
        
        return result;
    }
    
    // Column-major access (traverse by columns)
    vector<WeatherRecord> columnMajorAccess() {
        vector<WeatherRecord> result;
        auto start = chrono::high_resolution_clock::now();
        
        for (int j = 0; j < cities.size(); j++) {
            for (int i = 0; i < years.size(); i++) {
                if (weatherTable[i][j] != SENTINEL_VALUE) {
                    // Create a date string (simplified for this example)
                    string date = "01/01/" + to_string(years[i]);
                    WeatherRecord record(date, cities[j], weatherTable[i][j]);
                    result.push_back(record);
                }
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;
        cout << "Column-major access time: " << duration.count() << " ms" << endl;
        
        return result;
    }
    
    // Get the sentinel value
    double getSentinelValue() const {
        return SENTINEL_VALUE;
    }
    
    // Get all cities
    const vector<string>& getCities() const {
        return cities;
    }
    
    // Get all years
    const vector<int>& getYears() const {
        return years;
    }
    
    // Get the raw weather table
    const double (*getWeatherTable() const)[MAX_CITIES] {
        return weatherTable;
    }
};

#endif // DATA_STORAGE_H