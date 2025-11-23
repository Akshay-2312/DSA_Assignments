#pragma once
#include <string>

struct StudentRecord {
    int StudentID;
    std::string StudentName;
    double Marks;
    std::string CourseDetails;

    StudentRecord() : StudentID(0), Marks(0.0) {}
    StudentRecord(int id, const std::string& name, double marks, const std::string& course)
        : StudentID(id), StudentName(name), Marks(marks), CourseDetails(course) {}
};