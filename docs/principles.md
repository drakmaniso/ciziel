# Principles

## About elegance

Aim for simplicity and orthogonality of features, but allow for pragmatic
concessions. In other words, purity and its associated kind of elegance are not
a primary objective.


## About performance

Transforming data is the whole point of programming. The language should be
able to handle any data in computer memory directly. This means all values are
unboxed by default, and pointers are explicits.


## About correctness

"Program with data, not types"

The type system should be at the same time useful and helpful. This means
statical type checking, type inference and enough expressivity, but also
discouraging excessive type-level programming.


## About modularity

The correct level of encapsulation is the module. Encapsulation at type-level
leads to complex namespaces and over-engineering.

