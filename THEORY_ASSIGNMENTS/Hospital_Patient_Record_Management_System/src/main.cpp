#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "PatientRecord.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Polynomial.h"
#include "PostfixEvaluator.h"
using namespace std;

static void pauseAndClear() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x) return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n";
    }
}

static double readDouble(const string& prompt) {
    while (true) {
        cout << prompt;
        double x;
        if (cin >> x) return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n";
    }
}

static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin >> ws, s);
    return s;
}

int main() {
    LinkedList patients;
    UndoStack undo;
    EmergencyQueueManager emergency(EmergencyQueueType::Priority);

    while (true) {
        cout << "\n===== Hospital Patient Record Management System =====\n";
        cout << "1. Add Patient Record\n";
        cout << "2. Delete Patient by ID\n";
        cout << "3. Retrieve Patient by ID\n";
        cout << "4. Undo Last Admission\n";
        cout << "5. Manage Emergency Queue\n";
        cout << "6. Calculate Billing (Polynomials)\n";
        cout << "7. Evaluate Inventory (Postfix)\n";
        cout << "8. List All Patients\n";
        cout << "0. Exit\n";

        int choice = readInt("Select option: ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        switch (choice) {
        case 1: {
            int id = readInt("Enter Patient ID: ");
            string name = readLine("Enter Patient Name: ");
            string date = readLine("Enter Admission Date (YYYY-MM-DD): ");
            string details = readLine("Enter Treatment Details: ");
            PatientRecord p(id, name, date, details);
            if (patients.insertPatient(p)) {
                undo.push(id);
                cout << "Patient added and recorded in undo stack.\n";
            } else {
                cout << "Failed to add patient (allocation error).\n";
            }
            break;
        }
        case 2: {
            int id = readInt("Enter Patient ID to delete: ");
            bool ok = patients.deletePatient(id);
            cout << (ok ? "Deleted.\n" : "Patient not found.\n");
            break;
        }
        case 3: {
            int id = readInt("Enter Patient ID to retrieve: ");
            PatientRecord out;
            if (patients.retrievePatient(id, out)) {
                cout << "Found -> ID: " << out.patientID << ", Name: " << out.patientName
                     << ", Date: " << out.admissionDate << ", Treatment: " << out.treatmentDetails << '\n';
            } else {
                cout << "Patient not found.\n";
            }
            break;
        }
        case 4: {
            int id;
            if (undo.pop(id)) {
                bool ok = patients.deletePatient(id);
                cout << (ok ? "Undo successful. Last admission removed.\n" : "Undo failed. Record not found.\n");
            } else {
                cout << "Undo stack empty.\n";
            }
            break;
        }
        case 5: {
            cout << "\n-- Emergency Queue --\n";
            cout << "1. Set Queue Type (Circular/Priority)\n";
            cout << "2. Enqueue Emergency Patient\n";
            cout << "3. Dequeue Emergency Patient\n";
            cout << "4. Show Queue Size\n";
            int sub = readInt("Select option: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (sub == 1) {
                cout << "Select type: 0=Circular, 1=Priority: ";
                int t; cin >> t; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                emergency.setType(t == 0 ? EmergencyQueueType::Circular : EmergencyQueueType::Priority);
                cout << "Type set.\n";
            } else if (sub == 2) {
                int id = readInt("Enter Patient ID: ");
                string name = readLine("Enter Name: ");
                int severity = readInt("Enter Severity (1-10): ");
                EmergencyPatient ep{ id, name, severity };
                emergency.enqueue(ep);
                cout << "Enqueued emergency patient.\n";
            } else if (sub == 3) {
                EmergencyPatient out;
                if (emergency.dequeue(out)) {
                    cout << "Dequeued -> ID: " << out.patientID << ", Name: " << out.name << ", Severity: " << out.severity << '\n';
                } else {
                    cout << "Queue empty.\n";
                }
            } else if (sub == 4) {
                cout << "Queue size: " << emergency.size() << '\n';
            } else {
                cout << "Invalid option.\n";
            }
            break;
        }
        case 6: {
            cout << "\n-- Billing: Polynomial Operations --\n";
            int degA = readInt("Enter degree of Polynomial A: ");
            vector<double> cA(degA + 1);
            for (int i = 0; i <= degA; ++i) cA[i] = readDouble("A[" + to_string(i) + "] = ");
            Polynomial A(cA);

            int degB = readInt("Enter degree of Polynomial B: ");
            vector<double> cB(degB + 1);
            for (int i = 0; i <= degB; ++i) cB[i] = readDouble("B[" + to_string(i) + "] = ");
            Polynomial B(cB);

            Polynomial sum = Polynomial::add(A, B);
            Polynomial prod = Polynomial::multiply(A, B);

            cout << "A(x) = "; A.print();
            cout << "B(x) = "; B.print();
            cout << "A(x) + B(x) = "; sum.print();
            cout << "A(x) * B(x) = "; prod.print();

            double x = readDouble("Enter x (duration) to evaluate total bill: ");
            double total = prod.evaluate(x);
            cout << "Total Bill at x=" << x << " is " << total << '\n';
            break;
        }
        case 7: {
            cout << "\n-- Inventory: Postfix Evaluation --\n";
            string expr = readLine("Enter postfix expression (space-separated): ");
            try {
                double val = PostfixEvaluator::evaluate(expr);
                cout << "Result = " << val << '\n';
            } catch (const std::exception& ex) {
                cout << "Error: " << ex.what() << '\n';
            }
            break;
        }
        case 8: {
            patients.printAll();
            break;
        }
        default:
            cout << "Invalid option.\n";
        }
    }

    return 0;
}