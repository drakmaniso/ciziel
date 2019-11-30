# Grace

Grace is my ongoing project to design a simple functional language, and write
an compiler for it.


## Motivation

The intuition behind this project is that, due to the high performance of
modern computers and the evolution of compiler techniques, it should be
possible to implement a purely functional language that is efficient enough to
be useful for some tasks usually left to lower-level languages, such as game
development or embedded devices.


## Principles

Aim for simplicity and orthogonality of features, but allow for pragmatic
concessions. In other words, purity and its associated kind of elegance is not
an objective.

Transforming data is the whole point of programming. The language should be
able to handle any data in computer memory directly. This means all values are
unboxed by default, and references are explicits.

The type system should be at the same time useful and helpful. This means
statical type checking and type expressivity, but also simplicity (there should
be one obvious and correct way to describe data). 

The correct level of encapsulation is the module. Encapsulation at type-level
leads to over-engineering.

