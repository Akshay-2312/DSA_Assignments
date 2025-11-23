# ADT Explanation

## StudentRecord

- `StudentID`: unique integer roll number
- `StudentName`: string
- `Marks`: double
- `CourseDetails`: string

## Methods and System Integration

- Insert into hash table: ensures uniqueness and handles collisions via chaining.
- Search by roll: sequential over vector; binary over radix-sorted by ID.
- Sorting: marks by heap/quick; roll by radix.