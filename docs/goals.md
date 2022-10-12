# Goals

## Easy to read and easy to reason about

The main activity of a programmer is to *think* about code and data. When
designing a programming language, it's tempting to make it convenient to write.
But it's actually much more important to make it easy to read, and easy to
reason about. The language should help the programmer build a mental of the
codebase.

Corresponding characteristics:

- functions associated with types (aka methods);
- encapsulation at module-level only;
- orthogonality of features;
- low noise syntax;
- no automatic currying;
- high-level code;
- immutable data (referential transparency);

Maybe:

- supports both imperative and functional style?

## Focus on data

Ultimately, data is what matters: the only purpose of code is to manipulate data.

Correspongind characteristics:

- arrays instead of linked lists;
- low-level data (everything is value, explicit pointers);
- separation between methods and type definitions (using traits);

## Embrace change

Exploratory programming and refactoring are important.

Corresponding characteristics:

- static type checking (with local type inference);
- immutable data (and referential transparency);
- open sum types (no inheritance);

## Predictable performance

Although not a primary objective, it's important not to be wasteful.

---
[Back to index](index.md)
