# Motivation

The desire to design a new programming language came from my frustration with
two existing languages, Rust and Haskell, and the realisation that each of these
frustrations was actually the solution to the other.

## Rust, but simpler

Rust is a beautiful language. But because it is laser-focused on performance and
system programming, it has a lot of complexity. And no, I am not talking about
the borrow checker: this is the one thing I absolutely love in Rust.

I'm talking about all the design decisions made to satisfy the desire for
zero-cost abstractions, and maximum flexibility. Things like:
- the difference between functions and closures;
- borrowing and references are mixed together;
- the existence of mutable references, and two kind of borrowing;
- multiple dispatch (i.e. generic traits);
- the ability to implement traits for specific uses of generic types;
- the presence of unsafe code, which is always tempting;
- trait objects;
- macros;

None of those are essential to an ownership type system. They make sense for
Rust, because its goals. But what if you don't share most of these goals, but
still wanted automatic memory management through ownership?


## Haskell, but closer to the hardware

Haskell is also a really beautiful language. But it is also a very high-level
language, detached from how computers actually work. And no, I am not talking about the absence of mutation, the use of monads or the higher-kinded type-classes: those are great!

I'm talking about the lazy evaluation, which make thinking about what the code
actually does a lot harder. Lazyness forces you to think in term of
abstractions. Unfortunately, it is also very useful in a "pure" functional
language, in order to have decent performance.

I'm also talking about the use of linked lists as the main collection type.
Those are not well suited to current computer architecture (especially memory
caches).


## A beautiful synergy

Here are the two realisations that sparked the creation of Sona-Jo:
- Functional programming -- and especially referential transparency (aka
  "purity") -- can simplify the ownership system of Rust. Also, higher-order
  abstractions can bring flexibility without too much complexity;
- Ownership-base memory management can bring decent performance to a pure
  functional language, and allow the use arrays instead of linked lists.

It's the perfect match! At least when what you really want is a simple
functional language that is sufficiently close to the hardware.


---
[Back to index](index.md)