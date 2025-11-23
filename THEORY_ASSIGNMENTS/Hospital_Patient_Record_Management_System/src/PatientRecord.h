#ifndef PATIENT_RECORD_H
#define PATIENT_RECORD_H

#include <string>
using namespace std;

struct PatientRecord {
    int patientID;
    string patientName;
    string admissionDate;
    string treatmentDetails;

    PatientRecord()
        : patientID(0) {}

    PatientRecord(int id, const string& name,
                  const string& date,
                  const string& details)
        : patientID(id), patientName(name), admissionDate(date), treatmentDetails(details) {}
};

#endif