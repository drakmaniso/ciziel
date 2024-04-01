# Require getters for custom constructors

When a module define a custom constructor for a type, it must also define a getter function for each of the constructor arguments.

This requirement allows the compiler to automatically implement functional updates (`.with { ... }`).
