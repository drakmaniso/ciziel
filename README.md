# The Odo programming language

Odo is my ongoing project to design a simple functional language, and write a
compiler for it.


## Motivation

This project is born out of my longing for a functional language that would use
dynamic arrays instead of linked lists.


## Core design

The main idea behind the project the following synergy:

- Ownership should allow efficient use of arrays with no need for mutability.
- Immutability should make it easier to reason about ownership.

## Status

The feature set of the language is more or less decided, and so is the syntax.

The next step is to implement a parser, and then a compiler for a small subset
of the language. Probably written in C, and targeting C.

