#pragma once
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include "StudentRecord.h"

inline void printRecord(const StudentRecord& s) {
    std::cout << s.StudentID << " | " << s.StudentName << " | " << s.Marks << " | " << s.CourseDetails << "\n";
}

inline void printList(const std::vector<StudentRecord>& v, size_t limit = 0) {
    size_t n = v.size();
    size_t m = (limit == 0 || limit > n) ? n : limit;
    for (size_t i = 0; i < m; ++i) printRecord(v[i]);
}

inline bool isSortedByMarks(const std::vector<StudentRecord>& v) {
    for (size_t i = 1; i < v.size(); ++i) if (v[i-1].Marks > v[i].Marks) return false;
    return true;
}

inline bool isSortedByID(const std::vector<StudentRecord>& v) {
    for (size_t i = 1; i < v.size(); ++i) if (v[i-1].StudentID > v[i].StudentID) return false;
    return true;
}

inline std::vector<StudentRecord> generateRandomRecords(size_t n, unsigned seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count()) {
    std::vector<StudentRecord> v;
    v.reserve(n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> idDist(100000, 999999);
    std::uniform_real_distribution<double> markDist(0.0, 100.0);
    std::vector<int> used;
    used.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        int id = idDist(rng);
        bool unique = false;
        while (!unique) {
            unique = true;
            for (int u : used) if (u == id) { unique = false; id = idDist(rng); break; }
        }
        used.push_back(id);
        double marks = markDist(rng);
        std::string name = "Student_" + std::to_string(i+1);
        std::string course = "Course_" + std::to_string((i % 5) + 1);
        v.emplace_back(id, name, marks, course);
    }
    return v;
}

inline bool loadRecordsFromFile(const std::string& path, std::vector<StudentRecord>& out) {
    std::ifstream fin(path);
    if (!fin) return false;
    out.clear();
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string idStr, name, marksStr, course;
        if (!std::getline(iss, idStr, ',')) continue;
        if (!std::getline(iss, name, ',')) continue;
        if (!std::getline(iss, marksStr, ',')) continue;
        if (!std::getline(iss, course)) course = "";
        int id = std::stoi(idStr);
        double marks = std::stod(marksStr);
        out.emplace_back(id, name, marks, course);
    }
    return true;
}

inline bool saveRecordsToFile(const std::string& path, const std::vector<StudentRecord>& v, size_t limit = 0) {
    std::ofstream fout(path);
    if (!fout) return false;
    size_t n = v.size();
    size_t m = (limit == 0 || limit > n) ? n : limit;
    for (size_t i = 0; i < m; ++i) {
        fout << v[i].StudentID << "," << v[i].StudentName << "," << v[i].Marks << "," << v[i].CourseDetails << "\n";
    }
    return true;
}

inline bool writeRandomRecordsToFile(size_t n, const std::string& path) {
    auto v = generateRandomRecords(n);
    return saveRecordsToFile(path, v);
}