#pragma once
#include <string>
using namespace std;

struct StudentRecord {
    int studentID;
     string studentName;
    double grade;
     string courseDetails;

    StudentRecord() : studentID(-1), grade(0.0) {}
    StudentRecord(int id, const  string& name, double g, const  string& course)
        : studentID(id), studentName(name), grade(g), courseDetails(course) {}
};