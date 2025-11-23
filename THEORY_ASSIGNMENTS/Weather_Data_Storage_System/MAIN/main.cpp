#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include "WeatherRecord.h"
#include "DataStorage.h"
#include "SparseMatrix.h"

using namespace std;

// Function to display menu
void displayMenu() {
    cout << "\n===== Weather Data Storage System =====" << endl;
    cout << "1. Insert Weather Record" << endl;
    cout << "2. Delete Weather Record" << endl;
    cout << "3. Retrieve Weather Data" << endl;
    cout << "4. Display All Records (Row-Major)" << endl;
    cout << "5. Display All Records (Column-Major)" << endl;
    cout << "6. Convert to Sparse Matrix" << endl;
    cout << "7. Compare Dense vs Sparse Storage" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to get date input
string getDateInput() {
    string day, month, year;
    cout << "Enter day (DD): ";
    cin >> day;
    cout << "Enter month (MM): ";
    cin >> month;
    cout << "Enter year (YYYY): ";
    cin >> year;
    
    // Pad with leading zeros if necessary
    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;
    
    return day + "/" + month + "/" + year;
}

int main() {
    DataStorage storage;
    SparseMatrix* sparseMatrix = nullptr;
    int choice;
    
    // Sample data for testing
    vector<WeatherRecord> sampleData = {
        WeatherRecord("01/01/2020", "New York", 32.5),
        WeatherRecord("01/01/2020", "Los Angeles", 75.2),
        WeatherRecord("01/01/2020", "Chicago", 28.1),
        WeatherRecord("01/01/2021", "New York", 35.8),
        WeatherRecord("01/01/2021", "Los Angeles", 73.4),
        WeatherRecord("01/01/2021", "Chicago", 30.2),
        WeatherRecord("01/01/2022", "New York", 33.1),
        WeatherRecord("01/01/2022", "Los Angeles", 74.8),
        WeatherRecord("01/01/2022", "Chicago", 29.5)
    };
    
    // Insert sample data
    cout << "Inserting sample data..." << endl;
    for (const auto& record : sampleData) {
        storage.insert(record);
    }
    cout << "Sample data inserted successfully!" << endl;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Insert Weather Record
                string date = getDateInput();
                string city;
                double temp;
                
                cout << "Enter city name: ";
                cin.ignore();
                getline(cin, city);
                
                cout << "Enter temperature: ";
                cin >> temp;
                
                WeatherRecord record(date, city, temp);
                if (storage.insert(record)) {
                    cout << "Record inserted successfully!" << endl;
                } else {
                    cout << "Failed to insert record. Storage might be full." << endl;
                }
                break;
            }
            case 2: {
                // Delete Weather Record
                string city;
                int year;
                
                cout << "Enter city name: ";
                cin.ignore();
                getline(cin, city);
                
                cout << "Enter year: ";
                cin >> year;
                
                if (storage.deleteRecord(city, year)) {
                    cout << "Record deleted successfully!" << endl;
                } else {
                    cout << "Record not found or could not be deleted." << endl;
                }
                break;
            }
            case 3: {
                // Retrieve Weather Data
                string city;
                int year;
                
                cout << "Enter city name: ";
                cin.ignore();
                getline(cin, city);
                
                cout << "Enter year: ";
                cin >> year;
                
                double temp = storage.retrieve(city, year);
                if (temp != storage.getSentinelValue()) {
                    cout << "Temperature for " << city << " in " << year << ": " << temp << endl;
                } else {
                    cout << "No data found for " << city << " in " << year << endl;
                }
                break;
            }
            case 4: {
                // Display All Records (Row-Major)
                vector<WeatherRecord> records = storage.rowMajorAccess();
                cout << "\nAll Weather Records (Row-Major Access):" << endl;
                cout << setw(15) << "Date" << setw(20) << "City" << setw(15) << "Temperature" << endl;
                cout << string(50, '-') << endl;
                
                for (const auto& record : records) {
                    cout << setw(15) << record.getDate() 
                         << setw(20) << record.getCity() 
                         << setw(15) << record.getTemperature() << endl;
                }
                break;
            }
            case 5: {
                // Display All Records (Column-Major)
                vector<WeatherRecord> records = storage.columnMajorAccess();
                cout << "\nAll Weather Records (Column-Major Access):" << endl;
                cout << setw(15) << "Date" << setw(20) << "City" << setw(15) << "Temperature" << endl;
                cout << string(50, '-') << endl;
                
                for (const auto& record : records) {
                    cout << setw(15) << record.getDate() 
                         << setw(20) << record.getCity() 
                         << setw(15) << record.getTemperature() << endl;
                }
                break;
            }
            case 6: {
                // Convert to Sparse Matrix
                if (sparseMatrix != nullptr) {
                    delete sparseMatrix;
                }
                
                sparseMatrix = new SparseMatrix(
                    storage.getCities(),
                    storage.getYears(),
                    storage.getWeatherTable(),
                    storage.getYears().size(),
                    storage.getCities().size()
                );
                
                cout << "\nConverted to Sparse Matrix representation." << endl;
                sparseMatrix->printSparseMatrix();
                break;
            }
            case 7: {
                // Compare Dense vs Sparse Storage
                if (sparseMatrix == nullptr) {
                    cout << "Please convert to sparse matrix first (option 6)." << endl;
                    break;
                }
                
                cout << "\n===== Complexity Analysis: Dense vs Sparse =====" << endl;
                
                // Space complexity
                size_t denseSize = storage.getYears().size() * storage.getCities().size() * sizeof(double);
                size_t sparseSize = sparseMatrix->getMemoryUsage();
                
                cout << "Space Complexity:" << endl;
                cout << "Dense Matrix: " << denseSize << " bytes" << endl;
                cout << "Sparse Matrix: " << sparseSize << " bytes" << endl;
                cout << "Space Saving: " << (1.0 - (double)sparseSize / denseSize) * 100 << "%" << endl;
                
                // Time complexity demonstration
                cout << "\nTime Complexity:" << endl;
                
                // Measure row-major access time
                auto start1 = chrono::high_resolution_clock::now();
                storage.rowMajorAccess();
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration1 = end1 - start1;
                
                // Measure sparse matrix access time
                auto start2 = chrono::high_resolution_clock::now();
                sparseMatrix->getAllRecords();
                auto end2 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duration2 = end2 - start2;
                
                cout << "Dense Matrix Access: " << duration1.count() << " ms" << endl;
                cout << "Sparse Matrix Access: " << duration2.count() << " ms" << endl;
                
                cout << "\nOperation Complexity:" << endl;
                cout << "Operation\t\tDense\t\tSparse" << endl;
                cout << "Insert\t\t\tO(1)\t\tO(1)" << endl;
                cout << "Delete\t\t\tO(1)\t\tO(1)" << endl;
                cout << "Retrieve\t\tO(1)\t\tO(1)" << endl;
                cout << "Row-Major Access\tO(n×m)\t\tO(k)" << endl;
                cout << "Column-Major Access\tO(n×m)\t\tO(k)" << endl;
                cout << "Space\t\t\tO(n×m)\t\tO(k)" << endl;
                cout << "where n = years, m = cities, k = non-zero elements" << endl;
                break;
            }
            case 8:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);
    
    // Clean up
    if (sparseMatrix != nullptr) {
        delete sparseMatrix;
    }
    
    return 0;
}