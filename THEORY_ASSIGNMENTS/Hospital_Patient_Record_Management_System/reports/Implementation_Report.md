# Implementation Report

## Objective

Design and implement a Hospital Patient Record Management System using linked lists, stacks, and queues, with billing via polynomial operations and inventory via postfix evaluation.

## Patient Record ADT

- Attributes: `patientID`, `patientName`, `admissionDate`, `treatmentDetails`
- File: `src/PatientRecord.h`

## Data Structures Used

- Linked List (`src/LinkedList.h`): dynamic storage for patient records
- Stack (`src/Stack.h`): undo most recent admissions
- Queue (`src/Queue.h`): emergency handling with circular and priority variants

## Algorithms Implemented

- Polynomial operations (`src/Polynomial.h`): addition, multiplication, evaluation via Horner’s method
- Postfix evaluation (`src/PostfixEvaluator.h`): stack-based evaluation for inventory formulas

## Implementation Flow

1. Define `PatientRecord` ADT
2. Implement linked list operations: insert, delete (by ID), retrieve (by ID)
3. Implement undo mechanism via stack of patient IDs
4. Implement emergency queue: circular FIFO and priority max-heap by severity
5. Implement polynomial utilities for billing
6. Implement postfix evaluator for inventory
7. Integrate into menu-driven `main.cpp`

## Modules

- `main.cpp`: menu I/O and orchestration
- `LinkedList.h`: core admission store
- `Stack.h`: undo stack
- `Queue.h`: emergency queue manager
- `Polynomial.h`: billing math
- `PostfixEvaluator.h`: inventory math

## Menu Operations

- Add/Delete/Retrieve patient
- Undo last admission
- Manage emergency queue
- Calculate billing
- Evaluate inventory
- List all patients

## Testing

- Build and run; exercise menu paths with representative inputs
- Polynomial: verify addition/multiplication correctness and evaluation values
- Postfix: test valid/invalid expressions; confirm error messages
- Queue: test enqueue/dequeue order for circular and severity ordering for priority

## Screenshots (placeholders)

- `screenshots/output_patientlist.png`
- `screenshots/output_undo.png`
- `screenshots/output_queue.png`
- `screenshots/output_billing.png`
- `screenshots/output_postfix.png`

## Conclusion

The system integrates linear data structures to simulate common hospital workflows and demonstrates algorithmic billing/inventory computations with clear complexity characteristics.
