# Characteristics

## Static type checking

With local (global?) type inference.


## Ownership type system

Very similar to Rust, with one important difference: borrowing does not create a
reference. You can read a description of the ownership system
[here](ownership-system.md).


## Functional but in place

Thanks to the ownership system, we can always know when a "functional update"
will be made in-place (i.e. without copy).


## Arrays as the main collection type

Arrays as the main collection type, because doing everything with linked lists
is awkward and not well suited to modern computer architecture.


## Strict evaluation

Strict evaluation, because it is hard to predict the performance of lazy
evaluation.


## Open sum types

Open sum types, because they are a good middle-ground between algebraic data
types and object-oriented systems.

They are the only way to handle dynamic polymorphism in the language.


## Type classes

Type classes, because they offer a good way to group code and data while
preserving encapsulation.

Structural?


## Uncurried functions

**Uncurried** functions, because automatic currying makes code harder to read.


## Dot notation

Associating functions with types makes the code easier to reason about.


## High-level code with low-level data


## Encapsulation at the module level (and only there)


---
[Back to index](index.md)
