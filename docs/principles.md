# Principles


## Make thinking easier

The main activity of a programmer is to think about code and data. The language
design should reflect that: programs should be easy to read and reason about,
more than convenient to write. In other words, the language should help build a
mental model of the codebase.

Corresponding characteristics:
- supports both imperative and functional style;
- functions associated with types (aka methods);
- encapsulation at module-level only;
- orthogonality of features;
- low noise syntax;


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
- structural unions (no inheritance);
