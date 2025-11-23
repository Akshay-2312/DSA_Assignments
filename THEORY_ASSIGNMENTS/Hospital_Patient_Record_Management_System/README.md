# Hospital Patient Record Management System

## Overview

A menu-driven C++ application that manages hospital operations using linear data structures. It supports:

- Patient admissions with a `Linked List`
- Undo of recent admissions via a `Stack`
- Emergency handling via `Circular Queue` or `Priority Queue`
- Billing computations using `Polynomial` operations (add, multiply, evaluate)
- Inventory calculations using `Postfix` expression evaluation

## Setup

- Requirements: C++17 compiler (tested with `g++`), Windows/Unix shell
- Build:
  - `g++ src/main.cpp -o app.exe -std=c++17 -O2 -Wall -Wextra`
- Run:
  - Windows: `./app.exe`

## Directory Structure

```
Hospital_Patient_Record_Management_System/
├── src/
│   ├── main.cpp
│   ├── PatientRecord.h
│   ├── LinkedList.h
│   ├── Stack.h
│   ├── Queue.h
│   ├── Polynomial.h
│   ├── PostfixEvaluator.h
├── reports/
│   ├── Implementation_Report.md
│   ├── Complexity_Analysis.md
├── README.md
└── LICENSE
```

## Usage

Launch the executable and choose from the menu:

- 1 Add Patient Record: enter ID, name, date, treatment; pushed to undo stack
- 2 Delete Patient by ID: removes first match from linked list
- 3 Retrieve Patient by ID: prints patient details if found
- 4 Undo Last Admission: pops ID from undo stack and deletes from list
- 5 Manage Emergency Queue: set type, enqueue, dequeue, show size
- 6 Calculate Billing (Polynomials): input coefficients for A and B, then view sum/product and evaluate at `x`
- 7 Evaluate Inventory (Postfix): enter space-separated postfix expression
- 8 List All Patients: display all records

## Algorithms

- Linked List: tail insertion O(1), search/delete by ID O(n)
- Undo Stack: push/pop O(1)
- Circular Queue: enqueue/dequeue O(1)
- Priority Queue: enqueue/dequeue O(log n) using max-heap by severity
- Polynomial: addition O(n), multiplication O(n²), evaluation O(n) via Horner’s method
- Postfix: evaluation O(n)

## Examples

- Polynomial evaluation: if `A(x)=1+2x` and `B(x)=3`, product is `3+6x`, evaluating at `x=5` gives `33`.
- Postfix: `5 2 + 3 *` → `(5+2)*3=21`

## Notes

- Coefficients are provided in increasing power order: `a0, a1, a2, ...`
- Emergency queue defaults to `Priority`. Switch to `Circular` in the submenu if needed.

## License

MIT License. See `LICENSE`.
