# Ownership system

## Description

All values are either owned or shared. This distinction is especially important for pointers, but concerns also plain values.

Owned values behave like if they were a unique resource: they can be moved, or temporarily borrowed, but at any point of time, they can only be accessed through one (and only one) variable. This will be statically enforced by the compiler.

Shared values can be freely duplicated, and stored in multiple places. Pointers to the heap are reference-counted (using a modern algorithm like Perceus).

Transforming an owned value into a shared value has no performance cost. It's a
transformation on the type level: the underlying representation does not
change.

Transforming a shared value into an owned value may result in a copy, if the
reference count is not 1.


---
[Back to index](index.md)