# Ownership system

## Description

There is three kind of values in Sona-Jo: data values, unique values,
and shared values.

A **data value** can be freely copied. A variable holding this kind of value is
completely independent of all the other variables: the origin of the value does
not matter. Most programming languages use this behavior for their primitive
types (integer, boolean...).

A **unique value**, on the other hand, must always be owned by one (and only
one) variable, at all time. This ownership can be transferred from variable to
variable, but in doing so the previous owner become unusable.

A unique value can also be shared for a limited time, creating a **shared
value**. During the time a unique value is shared, the original owner become
inaccessible. A shared value can be copied and held by several variables at the
same time, but they are all tied by the same responsibility: their shared
origin. All variables sharing the same value are invalidated as soon as the
original owner is used again.


## Comparison with ownership in Rust

The ownership system of Sona-Jo is almost exactly the same as the one in Rust,
with two crucial differences.

The first difference with Rust is the absence of mutable borrowing (no
equivalent to `&mut`), since all values are immutable. Sona-Jo uses functional
updates instead of mutation.

But the most important difference with Rust is that borrowing (called sharing in
Sona-Jo) *does not create any reference*.

In Rust, the operator `&` does two things: it creates a reference to the
original value, and tell the type system that this reference is borrowed.

By contrast, in Sona-Jo, creating a reference and sharing are two distinct
things. When you share a unique value, you obtain a shared copy of this value,
not a shared pointer to it.


---
[Back to index](index.md)