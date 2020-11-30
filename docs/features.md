# The Odo programming language

Odo is a simple programming language with the following features:

- pure functions,
- type inference,
- ownership type system,
- algebraic data types,
- nominal typing for records,
- structural typing for unions,
- explicit structural conversions,
- zero-cost data abstractions,
- generic programming,
- higher-kinded type constraints.


## Pure functions

aka data immutability


## Type inference

full?


## Ownership type system

Two possibilities:

### Ownership a la Rust

...but with only one kind of shared reference, since everything is immutable.


### Ownership with dynamic alias checking

The type system tracks ownership, but in a different way than Rust:

- Only reference types can be owned.
- While the "one owner at all time" rule is statically checked, the "no shared
  alias while moving or mutating" rule is enforced at runtime, through a
  reference counting algorithm. See [1].

[1]: https://researcher.watson.ibm.com/researcher/files/us-bacon/Dingle07Ownership.pdf
(Adam Dingle and David F. Bacon, "Ownership You Can Count On: A Hybrid Approach to Safe Explicit Memory Management")


## Algebraic data types

aka sum types, tagged unions, enums


## Nominal typing for records


## Structural typing for variants


## Explicit structural conversion


## Zero-cost data abstractions

i.e. precise control of memory layout


## Generic programming


## Higher-kinded type constraints

aka generic constraints over type constructors

i.e. it is possible to define the concept of monads and functors in the type system

