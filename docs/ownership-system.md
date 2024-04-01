# Ownership system

## Description

There is three kind of values: shared, owned, and borrowed.

A **shared value** can be freely copied. A variable holding this kind of value is
completely independent of all the other variables: the origin of the value does
not matter. Most programming languages use this behavior for their primitive
types (integer, boolean...).

An **owned value**, on the other hand, can only be owned by one (and only one)
variable, at all time. This ownership can be transferred from variable to
variable, but in doing so the previous owner become unusable.

Finally, it's possible to create a **borrowed value** from a owned one, and it
will only exist for a limited time. During this time, the original owner (the
variable holding the owned value) become inaccessible. A borrowed value can be
copied and held by several variables at the same time, but they are all tied by
the same constraint: they cannot outlive the original owner of the value. All
variables borrowing the same value are invalidated as soon as the original owner
is used again.

It's possible to transform a shared value into an owned one, at the cost of a
potential deep copy (unless the compiler, or the runtime, can prove that the
shared value is actually unique).

## Comparison with ownership in Rust

The ownership system is almost exactly the same as the one in Rust, with two
important differences.

The first difference is that all values are immutable. This means there is no
mutable borrowing (no equivalent to `&mut`). Ciziel uses functional updates
instead of mutation.

But the most important difference with Rust is that borrowing (called sharing in
Sona-Jo) *does not create any reference*.

In Rust, the operator `&` does two things: it creates a reference to the
original value, and tell the type system that this reference is borrowed.

By contrast, in Sona-Jo, creating a reference and sharing are two distinct
things. When you share a unique value, you obtain a borrowed copy of this value,
not a lent pointer to it.

---
[Back to index](index.md)
