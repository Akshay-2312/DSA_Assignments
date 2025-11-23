# Complexity Analysis

## Summary Table

| Operation | Data Structure | Time Complexity | Space Complexity |
|---|---|---|---|
| Insert Patient (tail) | Linked List | O(1) | O(n) |
| Delete/Retrieve by ID | Linked List | O(n) | O(n) |
| Undo Admission (push/pop) | Stack | O(1) | O(n) |
| Emergency Enqueue/Dequeue | Circular Queue | O(1) | O(n) |
| Emergency Enqueue/Dequeue | Priority Queue (max-heap) | O(log n) | O(n) |
| Polynomial Addition | Array/List | O(n) | O(n) |
| Polynomial Multiplication | Array/List | O(n²) | O(n) |
| Polynomial Evaluation | Array/List | O(n) | O(n) |
| Postfix Evaluation | Stack | O(n) | O(n) |

## Notes
- `n` denotes the number of elements in the relevant structure (patients, terms, tokens).
- Linked list deletion/search scans nodes linearly.
- Priority queue implemented as a binary max-heap on severity; `enqueue` and `dequeue` are `heapify`-based.
- Polynomial evaluation uses Horner’s method for numerical stability and linear-time performance.
- Postfix evaluation uses a numeric stack; operators consume two operands and push the result.

## Assumptions
- Patient IDs are unique for typical workflows; deletion/undo are performed by ID.
- Polynomial coefficients are provided in increasing power order: `a0, a1, a2, ...`.
- Postfix input tokens are space-separated numbers and operators from `{+, -, *, /, ^}`.