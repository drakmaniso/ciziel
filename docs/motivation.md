# Why design a new language?

My initial motivation for this project came from the desire to find a language
that was both:

- purely functional,
- and reasonably close to the hardware.

I find it easier to construct a mental map of the codebase in a pure funcional
language (i.e. one with referential transparency). Which in turn leads to
better maintenance and easier debugging. It's always possible segment your code
and your data-structures into truly independent entities; something that is
rarely true in an imperative setting.

On the other hand, I also fint it important to not be wasteful with computer
resources. Modern computers are incredibly fast, and their storage capacity can
seem limitless. It is reasonable to sacrifice *some* performance when it makes
code simpler. But I think it's easy to go too far on this path, and modern
software sometimes feel much less responsive than their older counterpart.

This being said, designing and implementing a new language is a colossal task,
one which has almost zero chance to result in something that is actually used.

Therefore it's important to ask the question: what is lacking in existing
languages?


## What about Haskell?

Haskell is a really beautiful language. But it is also a very high-level
language, where it is difficult to understand how the code will perform.

It's not about the absence of mutation, or the extensive use of monads: lazy
evaluation is what makes the performance of Haskell code difficult to predict.
Unfortunately, laziness is also very useful in a "pure" functional language, in
order to have decent performance.

The use of linked lists as the main collection type is also a problem for
performance, since they are not well suited to current computer architecture
(especially memory caches).

We think both of these problems can be solved in a functional language by using
an ownership-base type system.


## What about Rust?

Rust is a fascinating, but complex language. Its complexity does not only come
from its ownership system. In fact, I think that most of it comes from being
laser-focused on performance and system programming.

Many design decisions seem to have been for the sake of achieving best
performance, zero-cost abstractions, and maximum flexibility:

- the difference between functions and closures;
- borrowing and references are mixed together;
- the existence of mutable references, and two kind of borrowing;
- multiple dispatch (i.e. generic traits);
- the ability to implement traits for specific uses of generic types;
- the presence of unsafe code, which is always tempting;
- trait objects;
- macros;

None of those are essential to an ownership type system. They make complete
sense for Rust, because of its goals. But what if you don't share most of these
goals, but still wanted to use ownership for automatic memory management?


## What about OCaml?

- module type system (elegant, but not easy to reason about);
- no type-classes/traits;


## What about Scala?

- JVM
- complexity


## What about Clojure?

- dynamic type system

---
[Back to index](index.md)