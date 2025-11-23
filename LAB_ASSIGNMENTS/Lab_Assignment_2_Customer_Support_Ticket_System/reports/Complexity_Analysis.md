# Complexity Analysis: Customer Support Ticket System

## Time & Space Complexity Table

| Operation | Data Structure | Time Complexity | Space Complexity | Explanation |
|-----------|----------------|----------------|-----------------|-------------|
| insertTicket() | Singly Linked List | O(1) (at tail) | O(1) | Insertion at the end of the list requires constant time when we maintain a tail pointer. Space complexity is constant as we only create one new node. |
| deleteTicket() | Singly Linked List | O(n) | O(1) | Deletion requires searching through the list to find the ticket with the specified ID, which takes linear time. Space complexity is constant as no additional storage is needed. |
| retrieveTicket() | Singly Linked List | O(n) | O(1) | Retrieval requires searching through the list to find the ticket with the specified ID, which takes linear time. Space complexity is constant as no additional storage is needed. |
| undoTicketOperation() | Stack | O(1) | O(n) | Popping from a stack takes constant time. Space complexity is linear with respect to the number of operations stored. |
| processPriorityTickets() | Priority Queue | O(log n) | O(n) | Extraction from a heap-based priority queue takes logarithmic time. Space complexity is linear with respect to the number of tickets stored. |
| processRoundRobinTickets() | Circular Queue | O(n) | O(n) | Processing all tickets in a circular queue takes linear time. Space complexity is linear with respect to the queue capacity. |
| compareBillingHistory() | Polynomial Linked List | O(m + n) | O(max(m, n)) | Comparing two polynomials requires traversing both lists, which takes time proportional to their combined sizes. Space complexity depends on the larger of the two polynomials. |

## Detailed Analysis

### Singly Linked List Operations

1. **insertTicket()**
   - Time Complexity: O(1) when inserting at the tail with a tail pointer
   - Without a tail pointer, insertion would be O(n) as we need to traverse to the end
   - Space Complexity: O(1) for creating a single new node

2. **deleteTicket()**
   - Time Complexity: O(n) as we need to search through the list to find the ticket
   - Best case: O(1) if the ticket to delete is at the head
   - Worst case: O(n) if the ticket is at the end or not found
   - Space Complexity: O(1) as no additional storage is needed

3. **retrieveTicket()**
   - Time Complexity: O(n) as we need to search through the list
   - Space Complexity: O(1) as we only return a pointer to an existing ticket

### Stack Operations

1. **push()**
   - Time Complexity: O(1) amortized for vector-based implementation
   - Space Complexity: O(1) for a single operation, O(n) overall

2. **pop()**
   - Time Complexity: O(1)
   - Space Complexity: O(1)

### Priority Queue Operations

1. **enqueue()**
   - Time Complexity: O(log n) for heap insertion
   - Space Complexity: O(1) for a single operation, O(n) overall

2. **dequeue()**
   - Time Complexity: O(log n) for heap extraction
   - Space Complexity: O(1)

### Circular Queue Operations

1. **enqueue()**
   - Time Complexity: O(1)
   - Space Complexity: O(1) for a single operation, O(n) overall for the queue capacity

2. **dequeue()**
   - Time Complexity: O(1)
   - Space Complexity: O(1)

### Polynomial Linked List Operations

1. **addTerm()**
   - Time Complexity: O(n) to find the correct position
   - Space Complexity: O(1) for a single term

2. **compare()**
   - Time Complexity: O(m + n) where m and n are the sizes of the two polynomials
   - Space Complexity: O(max(m, n)) for storing the result

## Optimization Opportunities

1. **Linked List**: Could be optimized with a hash map for O(1) retrieval and deletion by ID
2. **Priority Queue**: Current implementation is optimal for the required operations
3. **Circular Queue**: Current implementation is optimal for the required operations
4. **Polynomial Linked List**: Could use a hash map for faster term lookup by exponent