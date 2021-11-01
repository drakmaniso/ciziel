# The Odo programming language

Odo is my ongoing project to design a simple functional language, and write a
compiler for it.


## Motivation

The main idea behind the project is to combine functional programming with
ownership types.

The expected benefits over other functional languages (such as ML, haskell)
are:

- automatic static memory management (instead of garbage collection),
- arrays as the base collection type (instead of lists),
- easy control of inputs/outputs (owned resource handle instead of monads),

The expected benefits over other languages with ownership (such as Rust) are:

- simplicity (data immutability means a simpler ownership system),
- easier to reason about (pure functions make for better program structure).


## Status

The feature set of the language is more or less decided, and so is the syntax.

The next step is to implement a parser, and then a compiler for a small subset
of the language. Probably written in C, and targeting C.

