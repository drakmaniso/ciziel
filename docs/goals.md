# Goals

## Easy to read and easy to reason about

The main activity of a programmer is to think about code and data. The language
design should reflect that: programs should be easy to read and reason about,
more than convenient to write. In other words, the language should help build a
mental model of the codebase.

Corresponding characteristics:
- functions associated with types (aka methods);
- encapsulation at module-level only;
- orthogonality of features;
- low noise syntax;
- no automatic currying;

Maybe:
- supports both imperative and functional style?


## Focus on data

Ultimately, data is what matters: the only purpose of code is to manipulate data.

Correspongind characteristics:
- zero-cost data abstractions;
- functions associated with types (aka methods);


## Embrace change

Exploratory programming and refactoring are important.

Corresponding characteristics:
- static type checking with type inference;
- immutability with optional mutability;
- open sum types (no inheritance);


## Predictable performance

Although not a primary objective, it's important not to be wasteful.


---
[Back to index](index.md)
