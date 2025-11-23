#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <limits>
#include "StudentRecord.h"
#include "HashTable.h"
#include "Search.h"
#include "SortMarks.h"
#include "SortRollNumbers.h"
#include "Performance.h"
#include "Utils.h"

int main() {
    HashTable table(1031);
    std::vector<StudentRecord> sortedList;
    bool running = true;
    bool lastSortByMarks = false;
    {
        std::vector<StudentRecord> data;
        if (loadRecordsFromFile("data/sample_dataset_small.txt", data)) {
            for (const auto& s : data) table.insertStudent(s);
        }
    }
    while (running) {
        std::cout << "\n1. Add record\n2. Search record\n3. Sort by marks\n4. Sort by roll number\n5. Compare sorting algorithms\n6. Display sorted list\n7. Exit\nChoose: ";
        std::string choiceStr; if (!std::getline(std::cin, choiceStr)) return 0; if (choiceStr.empty()) { continue; }
        int choice = 0; try { choice = std::stoi(choiceStr); } catch (...) { std::cout << "Invalid choice\n"; continue; }
        if (choice == 1) {
            std::string line;
            std::cout << "Enter StudentID: ";
            if (!std::getline(std::cin, line)) { std::cout << "Input error\n"; continue; }
            int id = 0; try { id = std::stoi(line); } catch (...) { std::cout << "Invalid ID\n"; continue; }
            if (table.exists(id)) { std::cout << "Duplicate StudentID\n"; continue; }
            std::cout << "Enter Name: ";
            std::string name; if (!std::getline(std::cin, name) || name.empty()) { std::cout << "Invalid Name\n"; continue; }
            std::cout << "Enter Marks: ";
            if (!std::getline(std::cin, line)) { std::cout << "Input error\n"; continue; }
            double marks = 0.0; try { marks = std::stod(line); } catch (...) { std::cout << "Invalid Marks\n"; continue; }
            std::cout << "Enter Course: ";
            std::string course; if (!std::getline(std::cin, course) || course.empty()) { std::cout << "Invalid Course\n"; continue; }
            StudentRecord s(id, name, marks, course);
            bool ok = table.insertStudent(s);
            std::cout << (ok ? "Inserted\n" : "Insert failed\n");
        } else if (choice == 2) {
            std::cout << "Enter StudentID: ";
            std::string line; if (!std::getline(std::cin, line)) { std::cout << "Input error\n"; continue; }
            int id = 0; try { id = std::stoi(line); } catch (...) { std::cout << "Invalid ID\n"; continue; }
            std::cout << "1. Sequential 2. Binary: ";
            std::string tStr; if (!std::getline(std::cin, tStr)) { std::cout << "Input error\n"; continue; }
            int t = 1; try { t = std::stoi(tStr); } catch (...) { t = 1; }
            auto all = table.toVector();
            if (t == 1) {
                int idx = sequentialSearch(all, id);
                if (idx >= 0) printRecord(all[idx]); else std::cout << "Not found\n";
            } else {
                auto byID = radixSortByID(all);
                int idx = binarySearch(byID, id);
                if (idx >= 0) printRecord(byID[idx]); else std::cout << "Not found\n";
            }
        } else if (choice == 3) {
            auto all = table.toVector();
            std::cout << "1. Heap Sort 2. Quick Sort: ";
            std::string tStr; if (!std::getline(std::cin, tStr)) { std::cout << "Input error\n"; continue; }
            int t = 1; try { t = std::stoi(tStr); } catch (...) { t = 1; }
            if (t == 1) sortedList = heapSortByMarks(all); else sortedList = quickSortByMarks(all);
            std::cout << "Sorted by Marks\n";
            lastSortByMarks = true;
        } else if (choice == 4) {
            auto all = table.toVector();
            sortedList = radixSortByID(all);
            std::cout << "Sorted by Roll Number\n";
            lastSortByMarks = false;
        } else if (choice == 5) {
            compareSortingPerformance();
        } else if (choice == 6) {
            if (sortedList.empty()) std::cout << "Sorted list empty\n"; else printList(sortedList, 50);
        } else if (choice == 7) {
            running = false;
        }
    }
    return 0;
}