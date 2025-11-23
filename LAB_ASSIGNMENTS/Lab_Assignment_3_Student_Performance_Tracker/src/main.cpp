#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include "StudentRecord.h"
#include "HashTable.h"
#include "SortingAlgorithms.h"

using namespace std;

// Sequential search by ID
int sequentialSearchByID(const vector<StudentRecord>& arr, int id) {
    for (size_t i = 0; i < arr.size(); ++i) if (arr[i].studentID == id) return (int)i; return -1;
}
// Sequential search by name
int sequentialSearchByName(const vector<StudentRecord>& arr, const string& name) {
    for (size_t i = 0; i < arr.size(); ++i) if (arr[i].studentName == name) return (int)i; return -1;
}

// Binary search requires sorted array by key
int binarySearchByID(vector<StudentRecord> arr, int id) {
    sort(arr.begin(), arr.end(), [](const StudentRecord& a, const StudentRecord& b){ return a.studentID < b.studentID; });
    int l = 0, r = (int)arr.size() - 1;
    while (l <= r) { int m = l + (r - l) / 2; if (arr[m].studentID == id) return m; if (arr[m].studentID < id) l = m + 1; else r = m - 1; }
    return -1;
}
int binarySearchByName(vector<StudentRecord> arr, const string& name) {
    sort(arr.begin(), arr.end(), [](const StudentRecord& a, const StudentRecord& b){ return a.studentName < b.studentName; });
    int l = 0, r = (int)arr.size() - 1;
    while (l <= r) { int m = l + (r - l) / 2; if (arr[m].studentName == name) return m; if (arr[m].studentName < name) l = m + 1; else r = m - 1; }
    return -1;
}

struct StudentPerformanceTracker {
    HashTable hashTable;
    vector<StudentRecord> studentArray;
    vector<StudentRecord> sortedList; // by grade

    void addStudentRecord(int id, const string& name, double grade, const string& course) {
        StudentRecord rec(id, name, grade, course);
        hashTable.insert(rec);
        studentArray.push_back(rec);
        cout << "Added student: " << id << " - " << name << " (" << grade << ")\n";
    }

    void searchByStudent() {
        cout << "Search by: 1) ID  2) Name : ";
        int mode; cin >> mode; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Method: 1) Sequential  2) Binary : ";
        int method; cin >> method; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (mode == 1) {
            int id; cout << "Enter ID: "; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int idx = (method == 1) ? sequentialSearchByID(studentArray, id) : binarySearchByID(studentArray, id);
            if (idx >= 0) {
                auto rec = studentArray[idx];
                cout << "Found: ID=" << rec.studentID << ", Name=" << rec.studentName << ", Grade=" << rec.grade << ", Course=" << rec.courseDetails << "\n";
            } else cout << "Not found.\n";
        } else {
            string name; cout << "Enter Name: "; getline(cin, name);
            int idx = (method == 1) ? sequentialSearchByName(studentArray, name) : binarySearchByName(studentArray, name);
            if (idx >= 0) {
                auto rec = studentArray[idx];
                cout << "Found: ID=" << rec.studentID << ", Name=" << rec.studentName << ", Grade=" << rec.grade << ", Course=" << rec.courseDetails << "\n";
            } else cout << "Not found.\n";
        }
    }

    void sortByGrades() {
        cout << "Sort by grades using: 1) Bubble 2) Insertion 3) Merge 4) Quick : ";
        int choice; cin >> choice; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        sortedList = studentArray; // copy
        switch (choice) {
            case 1: bubbleSortGrades(sortedList); break;
            case 2: insertionSortGrades(sortedList); break;
            case 3: mergeSortGrades(sortedList); break;
            case 4: quickSortGrades(sortedList); break;
            default: cout << "Invalid choice.\n"; return;
        }
        cout << "Sorted (ascending by grade):\n";
        for (const auto& rec : sortedList) cout << rec.studentID << " - " << rec.studentName << " : " << rec.grade << "\n";
    }

    void rankByPerformance() {
        auto ranks = studentArray; // copy
        heapSortGradesDesc(ranks);
        cout << "Ranking (highest grade first):\n";
        int pos = 1; for (const auto& rec : ranks) cout << pos++ << ") " << rec.studentID << " - " << rec.studentName << " : " << rec.grade << "\n";
    }

    void viewHashTable() const { hashTable.display(); }

    void compareSortingComplexity() const {
        cout << "Algorithm             Best        Avg         Worst       Space\n";
        cout << "Sequential Search     O(1)       O(n)        O(n)        O(1)\n";
        cout << "Binary Search         O(1)       O(log n)    O(log n)    O(1)\n";
        cout << "Bubble Sort           O(n)       O(n^2)      O(n^2)      O(1)\n";
        cout << "Insertion Sort        O(n)       O(n^2)      O(n^2)      O(1)\n";
        cout << "Merge Sort            O(n log n) O(n log n)  O(n log n)  O(n)\n";
        cout << "Quick Sort            O(n log n) O(n log n)  O(n^2)      O(log n)\n";
        cout << "Heap Sort             O(n log n) O(n log n)  O(n log n)  O(1)\n";
        cout << "Hash Search           O(1)       O(1)        O(n)        O(n)\n";
    }
};

void displayMenu() {
    cout << "================ Student Performance Tracker ================\n";
    cout << "1. Add Student\n";
    cout << "2. Search Student (Sequential/Binary)\n";
    cout << "3. Sort Records by Grades (Bubble/Insertion/Merge/Quick)\n";
    cout << "4. Rank Students by Performance (Heap Sort)\n";
    cout << "5. View Hash Table (Collisions)\n";
    cout << "6. Compare Sorting Complexities\n";
    cout << "7. Display All Students\n";
    cout << "8. Exit\n";
    cout << "============================================================\n";
    cout << "Enter choice: ";
}

int main() {
    StudentPerformanceTracker spt;
    int choice;
    while (true) {
        displayMenu();
        if (!(cin >> choice)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            int id; string name; double grade; string course;
            cout << "Enter ID: "; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Grade: "; cin >> grade; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Course Details: "; getline(cin, course);
            spt.addStudentRecord(id, name, grade, course);
        } else if (choice == 2) {
            spt.searchByStudent();
        } else if (choice == 3) {
            spt.sortByGrades();
        } else if (choice == 4) {
            spt.rankByPerformance();
        } else if (choice == 5) {
            spt.viewHashTable();
        } else if (choice == 6) {
            spt.compareSortingComplexity();
        } else if (choice == 7) {
            cout << "All students (unsorted):\n";
            for (const auto& rec : spt.studentArray) cout << rec.studentID << " - " << rec.studentName << " : " << rec.grade << " | " << rec.courseDetails << "\n";
        } else if (choice == 8) {
            cout << "Goodbye!\n"; break;
        } else {
            cout << "Invalid choice.\n";
        }
        cout << "\n";
    }
    return 0;
}